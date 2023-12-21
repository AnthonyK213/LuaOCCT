#include "lTopAbs.h"

void luaocct_init_TopAbs(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(TopAbs)

      .Begin_Namespace(TopAbs_Orientation)
      .Bind_Enum(TopAbs_Orientation, TopAbs_FORWARD)
      .Bind_Enum(TopAbs_Orientation, TopAbs_REVERSED)
      .Bind_Enum(TopAbs_Orientation, TopAbs_INTERNAL)
      .Bind_Enum(TopAbs_Orientation, TopAbs_EXTERNAL)
      .End_Namespace()

      .Begin_Namespace(TopAbs_ShapeEnum)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_COMPOUND)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_COMPSOLID)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_SOLID)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_SHELL)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_FACE)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_WIRE)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_EDGE)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_VERTEX)
      .Bind_Enum(TopAbs_ShapeEnum, TopAbs_SHAPE)
      .End_Namespace()

      .Begin_Namespace(TopAbs_State)
      .Bind_Enum(TopAbs_State, TopAbs_IN)
      .Bind_Enum(TopAbs_State, TopAbs_OUT)
      .Bind_Enum(TopAbs_State, TopAbs_ON)
      .Bind_Enum(TopAbs_State, TopAbs_UNKNOWN)
      .End_Namespace()

      .Begin_Class(TopAbs)
      .Bind_Method_Static(TopAbs, Compose)
      .Bind_Method_Static(TopAbs, Reverse)
      .Bind_Method_Static(TopAbs, Complement)
      .Bind_Method_Static(TopAbs, ShapeTypeToString)
      .addStaticFunction(
          "ShapeTypeFromString",
          +[](Standard_CString typeString)
              -> std::tuple<Standard_Boolean, TopAbs_ShapeEnum> {
            TopAbs_ShapeEnum shapeEnum{TopAbs_ShapeEnum::TopAbs_SHAPE};
            Standard_Boolean ok =
                TopAbs::ShapeTypeFromString(typeString, shapeEnum);
            return {ok, shapeEnum};
          })
      .Bind_Method_Static(TopAbs, ShapeOrientationToString)
      .addStaticFunction(
          "ShapeOrientationFromString",
          +[](Standard_CString typeString)
              -> std::tuple<Standard_Boolean, TopAbs_Orientation> {
            TopAbs_Orientation orientation{TopAbs_Orientation::TopAbs_FORWARD};
            Standard_Boolean ok =
                TopAbs::ShapeOrientationFromString(typeString, orientation);
            return {ok, orientation};
          })
      .End_Class()

      .End_Namespace1();
}
