#ifndef _LuaOCCT_lBRepBuilderAPI_Header
#define _LuaOCCT_lBRepBuilderAPI_Header

#include <BRepBuilderAPI.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

#include "lbind.h"

void luaocct_init_BRepBuilderAPI(lua_State *L);

#endif
