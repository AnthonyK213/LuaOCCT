#ifndef _LuaOCCT_HeaderFile
#define _LuaOCCT_HeaderFile

#ifndef __cplusplus
/* clang-format off */
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "luajit.h"
/* clang-format on */
#else
#include <lua.hpp>
#ifdef _WIN32
#define LuaOCCT_EXPORT extern "C" __declspec(dllexport)
#else
#define LuaOCCT_EXPORT extern "C"
#endif
#endif

LuaOCCT_EXPORT int luaopen_luaocct(lua_State *L);

#undef LuaOCCT_EXPORT

#endif
