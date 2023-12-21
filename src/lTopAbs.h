#ifndef _LuaOCCT_lTopAbs_Header
#define _LuaOCCT_lTopAbs_Header

#include <TopAbs.hxx>
#include <TopAbs_Orientation.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopAbs_State.hxx>

#include "lbind.h"

void luaocct_init_TopAbs(lua_State *L);

#endif
