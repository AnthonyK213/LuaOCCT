#include "lTopExp.h"

void luaocc_init_TopExp(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(TopExp)

      .Begin_Class(TopExp)
      .End_Class()

      .Begin_Class(TopExp_Explorer)
      .addConstructor<void(),
                      void(const TopoDS_Shape &, const TopAbs_ShapeEnum),
                      void(const TopoDS_Shape &, const TopAbs_ShapeEnum,
                           const TopAbs_ShapeEnum)>()
      .Bind_Method(TopExp_Explorer, Init)
      .Bind_Method(TopExp_Explorer, More)
      .Bind_Method(TopExp_Explorer, Next)
      .Bind_Method(TopExp_Explorer, Value)
      .Bind_Method(TopExp_Explorer, Current)
      .Bind_Method(TopExp_Explorer, ReInit)
      .Bind_Method(TopExp_Explorer, ExploredShape)
      .Bind_Method(TopExp_Explorer, Depth)
      .Bind_Method(TopExp_Explorer, Clear)
      .End_Class()

      .End_Namespace1();
}
