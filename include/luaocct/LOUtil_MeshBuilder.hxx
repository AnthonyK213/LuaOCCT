#ifndef _LuaOCCT_LOUtil_MeshBuilder_HeaderFile
#define _LuaOCCT_LOUtil_MeshBuilder_HeaderFile

#include <Poly_Triangulation.hxx>
#include <TopLoc_Location.hxx>

#include <vector>

class LOUtil_MeshBuilder {
public:
  Standard_EXPORT LOUtil_MeshBuilder();

public:
  Standard_EXPORT Standard_Boolean Add(Handle(Poly_Triangulation) theMesh,
                                       const TopLoc_Location &theLocation);

  Standard_EXPORT void Clear();

  Standard_EXPORT Handle(Poly_Triangulation) Mesh() const;

  Standard_EXPORT void Transform(const gp_Trsf &theT);

private:
  std::vector<gp_Pnt> myNodes{};
  std::vector<Poly_Triangle> myTriangles{};
};

#endif
