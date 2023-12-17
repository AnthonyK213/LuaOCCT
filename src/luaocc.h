#ifndef _LuaOCC_Header
#define _LuaOCC_Header

// clang-format off
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
// clang-format on

#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>

#ifdef _WIN32
#define LuaOCC_Export extern "C" __declspec(dllexport)
#else
#define LuaOCC_Export extern "C"
#endif

LuaOCC_Export int init(lua_State *L);

#endif
