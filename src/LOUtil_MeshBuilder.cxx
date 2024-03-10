#include <luaocct/LOUtil_MeshBuilder.hxx>

LOUtil_MeshBuilder::LOUtil_MeshBuilder() {}

Standard_Boolean LOUtil_MeshBuilder::Add(Handle(Poly_Triangulation) theMesh,
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

void LOUtil_MeshBuilder::Clear() {
  myNodes.clear();
  myTriangles.clear();
}

Handle(Poly_Triangulation) LOUtil_MeshBuilder::Mesh() const {
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

void LOUtil_MeshBuilder::Transform(const gp_Trsf &theT) {
  for (gp_Pnt &aNode : myNodes) {
    aNode.Transform(theT);
  }
}
