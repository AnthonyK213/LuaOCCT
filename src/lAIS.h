#ifndef _LuaOCCT_lAIS_Header
#define _LuaOCCT_lAIS_Header

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>

#include "lbind.h"

int32_t luaocct_init_AIS(lua_State *L);

#endif
