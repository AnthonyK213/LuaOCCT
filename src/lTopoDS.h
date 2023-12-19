#ifndef _LuaOCC_lTopoDS_Header
#define _LuaOCC_lTopoDS_Header

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>

#include "bind.h"

int32_t luaocc_init_TopoDS(lua_State *L);

#endif
