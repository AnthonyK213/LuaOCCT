#include "lBRepLib.h"

void luaocct_init_BRepLib(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(BRepLib)

      .Begin_Class(BRepLib)
      .addStaticFunction(
          "Plane",
          luabridge::overload<const Handle(Geom_Plane) &>(&BRepLib::Plane),
          luabridge::overload<>(&BRepLib::Plane))
      .addStaticFunction(
          "Precision",
          luabridge::overload<const Standard_Real>(&BRepLib::Precision),
          luabridge::overload<>(&BRepLib::Precision))
      .Bind_Method_Static(BRepLib, BuildCurve3d)
      .addStaticFunction(
          "BuildCurves3d",
          luabridge::overload<const TopoDS_Shape &, const Standard_Real,
                              const GeomAbs_Shape, const Standard_Integer,
                              const Standard_Integer>(&BRepLib::BuildCurves3d),
          luabridge::overload<const TopoDS_Shape &>(&BRepLib::BuildCurves3d))
      .End_Class()

      .End_Namespace1();
}
