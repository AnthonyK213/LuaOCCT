#ifndef _LuaOCC_bind_Header
#define _LuaOCC_bind_Header

#include <lua.hpp>

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

#define LuaBridge__G(L) luabridge::getGlobalNamespace(L)

#define Begin_Namespace0() beginNamespace("LuaOCC")
#define Begin_Namespace1(U) beginNamespace("LuaOCC").beginNamespace(#U)
#define Begin_Namespace2(U, V)                                                 \
  beginNamespace("LuaOCC").beginNamespace(#U).beginNamespace(#V)
#define End_Namespace0() endNamespace()
#define End_Namespace1() endNamespace().endNamespace()
#define End_Namespace2() endNamespace().endNamespace().endNamespace()

#define Begin_Class(T) beginClass<T>(#T)
#define End_Class() endClass()

#define Begin_Derive(D, B) deriveClass<D, B>(#D)
#define End_Derive() endClass()

#define Bind_Enum(E, V) addVariable(#V, E::V)

#define Bind_Property(T, G, S)                                                 \
  addProperty(#G, &T::G, &T::S).addFunction(#S, &T::S)
#define Bind_Property_Readonly(T, G) addProperty(#G, &T::G)

#define Bind_Method(T, M) addFunction(#M, &T::M)
#define Bind_Method_Static(T, M) addStaticFunction(#M, &T::M)

#endif
