#ifndef _LuaOCCT_util_shape_HeaderFile
#define _LuaOCCT_util_shape_HeaderFile

#include <IMeshTools_Parameters.hxx>
#include <Poly_Triangulation.hxx>
#include <TopoDS_Shape.hxx>

#include <vector>

namespace luaocct {
namespace util {
namespace Shape {

class MeshBuilder {
public:
  Standard_EXPORT MeshBuilder();

  Standard_EXPORT ~MeshBuilder();

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

} // namespace Shape
} // namespace util
} // namespace luaocct

namespace luaocct {
namespace util {
namespace Shape {

Standard_EXPORT Handle(Poly_Triangulation)
    ToMesh(const TopoDS_Shape &theShape, const TopLoc_Location &theLocation,
           const IMeshTools_Parameters &theParam = IMeshTools_Parameters());

} // namespace Shape
} // namespace util
} // namespace luaocct

#endif
