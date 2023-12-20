#include "lutil.h"

namespace luaocc {
namespace util {
namespace curve {

static Standard_Real GetLength(const Handle(Geom_Curve) & theCurve) {
  return GetLength(theCurve, theCurve->FirstParameter(),
                   theCurve->LastParameter());
}

static Standard_Real GetLength(const Handle(Geom_Curve) & theCurve,
                               const Standard_Real t0, const Standard_Real t1) {
  GeomAdaptor_Curve aCrv(theCurve);
  return CPnts_AbscissaPoint::Length(aCrv, t0, t1);
}

} // namespace curve
} // namespace util
} // namespace luaocc

int32_t luaocc_init_util(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace2(util, curve)
      .addFunction(
          "GetLength",
          luabridge::overload<const Handle(Geom_Curve) &>(
              &luaocc::util::curve::GetLength),
          luabridge::overload<const Handle(Geom_Curve) &, const Standard_Real,
                              const Standard_Real>(
              &luaocc::util::curve::GetLength))
      .End_Namespace2();

  return 0;
}
