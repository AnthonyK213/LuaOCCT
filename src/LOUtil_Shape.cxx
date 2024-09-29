#include <luaocct/LOUtil_MeshBuilder.hxx>
#include <luaocct/LOUtil_Shape.hxx>

#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_TFace.hxx>
#include <BRep_Tool.hxx>
#include <Poly_ListOfTriangulation.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>

Handle(Poly_Triangulation) LOUtil_Shape::ToMesh(
    const TopoDS_Shape &theShape, const TopLoc_Location &theLocation,
    const IMeshTools_Parameters &theMeshParams) {
  if (theShape.IsNull())
    return nullptr;

  LOUtil_MeshBuilder aMeshBuilder{};

  /* TopoDS_Face mesh backup, to preserve the triangulation in the view. */
  std::vector<Poly_ListOfTriangulation> polysBackup{};
  std::vector<Handle(Poly_Triangulation)> activePolyBackup{};

  /* Backup the meshes then clear them, or the param may not take effect. */
  for (TopExp_Explorer ex(theShape, TopAbs_FACE); ex.More(); ex.Next()) {
    TopoDS_Face face = TopoDS::Face(ex.Current());
    Handle(BRep_TFace) tFace = Handle(BRep_TFace)::DownCast(face.TShape());

    if (tFace.IsNull())
      continue;

    polysBackup.push_back(tFace->Triangulations());
    activePolyBackup.push_back(tFace->ActiveTriangulation());

    tFace->Triangulations(Poly_ListOfTriangulation(), nullptr);
  }

  BRepMesh_IncrementalMesh aMesher(theShape, theMeshParams);

  Standard_Integer faceIndex = 0;

  for (TopExp_Explorer ex(theShape, TopAbs_FACE); ex.More(); ex.Next()) {
    TopoDS_Face face = TopoDS::Face(ex.Current());

    TopLoc_Location loc;
    Handle(Poly_Triangulation) facing = BRep_Tool::Triangulation(face, loc);

    /* Recover the original mesh. */
    Handle(BRep_TFace) tFace = Handle(BRep_TFace)::DownCast(face.TShape());

    if (!tFace.IsNull()) {
      tFace->Triangulations(polysBackup[faceIndex],
                            activePolyBackup[faceIndex]);
      faceIndex++;
    }

    if (facing.IsNull())
      continue;

    aMeshBuilder.Add(facing, loc);
  }

  aMeshBuilder.Transform(theLocation.Transformation());

  Handle(Poly_Triangulation) aMesh = aMeshBuilder.Mesh();
  aMeshBuilder.Clear();

  if (aMesh.IsNull())
    return nullptr;

  aMesh->ComputeNormals();

  return aMesh;
}
