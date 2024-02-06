#include "util_shape.h"

#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_TFace.hxx>
#include <BRep_Tool.hxx>
#include <Poly_ListOfTriangulation.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>

namespace luaocct {
namespace util {
namespace Shape {

MeshBuilder::MeshBuilder() {}

MeshBuilder::~MeshBuilder() {}

Standard_Boolean MeshBuilder::Add(Handle(Poly_Triangulation) theMesh,
                                  const TopLoc_Location &theLocation) {
  Standard_Integer nbNodes = static_cast<Standard_Integer>(myNodes.size());

  for (Standard_Integer i = 1; i <= theMesh->NbNodes(); ++i) {
    gp_Pnt aNode = theMesh->Node(i);
    aNode.Transform(theLocation);
    myNodes.push_back(aNode);
  }

  for (Standard_Integer i = 1; i <= theMesh->NbTriangles(); ++i) {
    const Poly_Triangle &triangle = theMesh->Triangle(i);
    myTriangles.push_back(
        {nbNodes + triangle(1), nbNodes + triangle(2), nbNodes + triangle(3)});
  }

  return Standard_True;
}

void MeshBuilder::Clear() {
  myNodes.clear();
  myTriangles.clear();
}

Handle(Poly_Triangulation) MeshBuilder::Mesh() const {
  if (myNodes.empty() || myTriangles.empty()) {
    return nullptr;
  }

  TColgp_Array1OfPnt aPoints{1, (Standard_Integer)myNodes.size()};
  Poly_Array1OfTriangle aTriangles{1, (Standard_Integer)myTriangles.size()};

  for (Standard_Integer i = 0; i < myNodes.size(); ++i) {
    aPoints.SetValue(i + 1, myNodes[i]);
  }

  for (Standard_Integer i = 0; i < myTriangles.size(); ++i) {
    aTriangles.SetValue(i + 1, myTriangles[i]);
  }

  return new Poly_Triangulation(aPoints, aTriangles);
}

void MeshBuilder::Transform(const gp_Trsf &theT) {
  for (gp_Pnt &aNode : myNodes) {
    aNode.Transform(theT);
  }
}

} // namespace Shape
} // namespace util
} // namespace luaocct

namespace luaocct {
namespace util {
namespace Shape {

Handle(Poly_Triangulation)
    ToMesh(const TopoDS_Shape &theShape, const TopLoc_Location &theLocation,
           const IMeshTools_Parameters &theMeshParams) {
  if (theShape.IsNull())
    return nullptr;

  MeshBuilder aMeshBuilder{};

  /// TopoDS_Face mesh backup, to preserve the triangulation in the view.
  std::vector<Poly_ListOfTriangulation> polysBackup{};
  std::vector<Handle(Poly_Triangulation)> activePolyBackup{};

  /// Backup the meshes then clear them, or the param may not take effect.
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

    /// Recover the original mesh.
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

} // namespace Shape
} // namespace util
} // namespace luaocct
