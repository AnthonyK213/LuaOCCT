#include "lStandard.h"

int32_t luaocc_init_Standard(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(Standard)
      .Begin_Class(Standard_Transient)
      .addConstructorFrom<Handle(Standard_Transient), void(),
                          void(const Standard_Transient &)>()
      .Bind_Method(Standard_Transient, Delete)
      .Bind_Method(Standard_Transient, DynamicType)
      .addFunction("IsInstance",
                   luabridge::overload<const Handle(Standard_Type) &>(
                       &Standard_Transient::IsInstance),
                   luabridge::overload<const Standard_CString>(
                       &Standard_Transient::IsInstance))
      .addFunction("IsKind",
                   luabridge::overload<const Handle(Standard_Type) &>(
                       &Standard_Transient::IsKind),
                   luabridge::overload<const Standard_CString>(
                       &Standard_Transient::IsKind))
      .Bind_Method(Standard_Transient, GetRefCount)
      .Bind_Method(Standard_Transient, IncrementRefCounter)
      .Bind_Method(Standard_Transient, DecrementRefCounter)
      .End_Class()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(Standard)
      .Begin_Derive(Standard_Type, Standard_Transient)
      .Bind_Method(Standard_Type, SystemName)
      .Bind_Method(Standard_Type, Name)
      .Bind_Method(Standard_Type, Size)
      .Bind_Method(Standard_Type, Parent)
      .addFunction(
          "SubType",
          luabridge::overload<const Handle(Standard_Type) &>(
              &Standard_Type::SubType),
          luabridge::overload<const Standard_CString>(&Standard_Type::SubType))
      .End_Derive()
      .End_Namespace1();

  return 0;
}
