#ifndef _LuaOCCT_LOUtil_Shape_HeaderFile
#define _LuaOCCT_LOUtil_Shape_HeaderFile

#include <IMeshTools_Parameters.hxx>
#include <Poly_Triangulation.hxx>
#include <TopoDS_Shape.hxx>

#include <vector>

class LOUtil_Shape {
public:
  Standard_EXPORT static Handle(Poly_Triangulation)
      ToMesh(const TopoDS_Shape &theShape, const TopLoc_Location &theLocation,
             const IMeshTools_Parameters &theParam = IMeshTools_Parameters());
};

#endif
