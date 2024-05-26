#ifndef _LuaOCCT_HeaderFile
#define _LuaOCCT_HeaderFile

#include <cstdint>
#include <lua.hpp>

#ifdef _WIN32
#define LuaOCCT_Export extern "C" __declspec(dllexport)
#else
#define LuaOCCT_Export extern "C"
#endif

LuaOCCT_Export int32_t luaopen_luaocct(lua_State *L);

#undef LuaOCCT_Export

#endif
