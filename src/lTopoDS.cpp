#include "lTopoDS.h"

#define Bind_TopoDS(C)                                                         \
  addStaticFunction(#C, luabridge::overload<const TopoDS_Shape &>(&TopoDS::C), \
                    luabridge::overload<TopoDS_Shape &>(&TopoDS::C))

#define Bind_TopoDS_Shape_Bool_Prop(P)                                         \
  addFunction(#P, luabridge::overload<>(&TopoDS_Shape::P),                     \
              luabridge::overload<Standard_Boolean>(&TopoDS_Shape::P))

#define Bind_TopoDS_Shape_Derive(C)                                            \
  Begin_Derive(TopoDS_##C, TopoDS_Shape).addConstructor<void()>().End_Derive()

void luaocct_init_TopoDS(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(TopoDS)

      .Begin_Class(TopoDS)
      .Bind_TopoDS(Vertex)
      .Bind_TopoDS(Edge)
      .Bind_TopoDS(Wire)
      .Bind_TopoDS(Face)
      .Bind_TopoDS(Shell)
      .Bind_TopoDS(Solid)
      .Bind_TopoDS(CompSolid)
      .Bind_TopoDS(Compound)
      .End_Class()

      .Begin_Class(TopoDS_Shape)
      .addConstructor<void()>()
      .Bind_Method(TopoDS_Shape, IsNull)
      .Bind_Method(TopoDS_Shape, Nullify)
      .addFunction(
          "Location", luabridge::overload<>(&TopoDS_Shape::Location),
          luabridge::overload<const TopLoc_Location &, const Standard_Boolean>(
              &TopoDS_Shape::Location))
      .Bind_Method(TopoDS_Shape, Located)
      .addFunction(
          "Orientation", luabridge::overload<>(&TopoDS_Shape::Orientation),
          luabridge::overload<TopAbs_Orientation>(&TopoDS_Shape::Orientation))
      .Bind_Method(TopoDS_Shape, Oriented)
      .Bind_Method(TopoDS_Shape, ShapeType)
      .Bind_TopoDS_Shape_Bool_Prop(Free)
      .Bind_TopoDS_Shape_Bool_Prop(Locked)
      .Bind_TopoDS_Shape_Bool_Prop(Modified)
      .Bind_TopoDS_Shape_Bool_Prop(Checked)
      .Bind_TopoDS_Shape_Bool_Prop(Orientable)
      .Bind_TopoDS_Shape_Bool_Prop(Closed)
      .Bind_TopoDS_Shape_Bool_Prop(Infinite)
      .Bind_TopoDS_Shape_Bool_Prop(Convex)
      .Bind_Method(TopoDS_Shape, Move)
      .Bind_Method(TopoDS_Shape, Moved)
      .Bind_Method(TopoDS_Shape, Reverse)
      .Bind_Method(TopoDS_Shape, Reversed)
      .Bind_Method(TopoDS_Shape, Complement)
      .Bind_Method(TopoDS_Shape, Complemented)
      .Bind_Method(TopoDS_Shape, Compose)
      .Bind_Method(TopoDS_Shape, Composed)
      .Bind_Method(TopoDS_Shape, NbChildren)
      .Bind_Method(TopoDS_Shape, IsPartner)
      .Bind_Method(TopoDS_Shape, IsSame)
      .Bind_Method(TopoDS_Shape, IsEqual)
      .Bind_Method(TopoDS_Shape, IsNotEqual)
      .Bind_Method(TopoDS_Shape, HashCode)
      .Bind_Method(TopoDS_Shape, EmptyCopy)
      .Bind_Method(TopoDS_Shape, EmptyCopied)
      .addFunction("TShape", luabridge::overload<>(&TopoDS_Shape::TShape),
                   luabridge::overload<const Handle(TopoDS_TShape) &>(
                       &TopoDS_Shape::TShape))
      .addFunction("__eq", &TopoDS_Shape::IsEqual)
      .End_Class()
      
      .Bind_TopoDS_Shape_Derive(Vertex)
      .Bind_TopoDS_Shape_Derive(Edge)
      .Bind_TopoDS_Shape_Derive(Wire)
      .Bind_TopoDS_Shape_Derive(Face)
      .Bind_TopoDS_Shape_Derive(Shell)
      .Bind_TopoDS_Shape_Derive(Solid)
      .Bind_TopoDS_Shape_Derive(CompSolid)
      .Bind_TopoDS_Shape_Derive(Compound)

      .End_Namespace1();
}
