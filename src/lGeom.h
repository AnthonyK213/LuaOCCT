#ifndef _LuaOCC_lGeom_Header
#define _LuaOCC_lGeom_Header

#include <Geom_BSplineCurve.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <gp_Lin.hxx>

#include "bind.h"

int32_t luaocc_init_Geom(lua_State *L);

#endif
