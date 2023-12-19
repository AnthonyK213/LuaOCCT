#ifndef _LuaOCC_Header
#define _LuaOCC_Header

#include <cstdint>
#include <lua.hpp>

#ifdef _WIN32
#define LuaOCC_Export extern "C" __declspec(dllexport)
#else
#define LuaOCC_Export extern "C"
#endif

LuaOCC_Export int32_t luaopen_luaocc(lua_State *L);

#undef LuaOCC_Export

#endif
