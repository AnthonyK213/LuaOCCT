#ifndef _LuaOCCT_util_Header
#define _LuaOCCT_util_Header

#include <CPnts_AbscissaPoint.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_Curve.hxx>

#include "lbind.h"

namespace luaocct {
namespace util {
namespace Curve {

static Standard_Real GetLength(const Handle(Geom_Curve) & theCurve);

static Standard_Real GetLength(const Handle(Geom_Curve) & theCurve,
                               const Standard_Real t0, const Standard_Real t1);

} // namespace curve
} // namespace util
} // namespace luaocc

void luaocct_init_util(lua_State *L);

#endif
