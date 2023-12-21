#include "lBRep.h"

void luaocc_init_BRep(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(BRep)

      .Begin_Class(BRep_Tool)
      .addStaticFunction(
          "IsClosed",
          luabridge::overload<const TopoDS_Shape &>(&BRep_Tool::IsClosed),
          luabridge::overload<const TopoDS_Edge &, const TopoDS_Face &>(
              &BRep_Tool::IsClosed),
          luabridge::overload<const TopoDS_Edge &, const Handle(Geom_Surface) &,
                              const TopLoc_Location &>(&BRep_Tool::IsClosed),
          luabridge::overload<const TopoDS_Edge &,
                              const Handle(Poly_Triangulation) &,
                              const TopLoc_Location &>(&BRep_Tool::IsClosed))
      .addStaticFunction(
          "Surface",
          luabridge::overload<const TopoDS_Face &, TopLoc_Location &>(
              &BRep_Tool::Surface),
          luabridge::overload<const TopoDS_Face &>(&BRep_Tool::Surface))
      .addStaticFunction(
          "Tolerance",
          luabridge::overload<const TopoDS_Face &>(&BRep_Tool::Tolerance),
          luabridge::overload<const TopoDS_Vertex &>(&BRep_Tool::Tolerance))
      .Bind_Method_Static(BRep_Tool, NaturalRestriction)
      .addStaticFunction(
          "IsGeometric",
          luabridge::overload<const TopoDS_Face &>(&BRep_Tool::IsGeometric),
          luabridge::overload<const TopoDS_Edge &>(&BRep_Tool::IsGeometric))
      .addStaticFunction(
          "Curve",
          +[](const TopoDS_Edge &edge)
              -> std::tuple<Handle(Geom_Curve), Standard_Real, Standard_Real> {
            TopLoc_Location location{};
            Standard_Real first, last;
            Handle(Geom_Curve) curve =
                BRep_Tool::Curve(edge, location, first, last);
            return {curve, first, last};
          })
      .Bind_Method_Static(BRep_Tool, Pnt)
      .End_Class()

      .End_Namespace1();
}
