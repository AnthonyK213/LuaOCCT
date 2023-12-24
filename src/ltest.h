#ifndef _LuaOCCT_test_Header
#define _LuaOCCT_test_Header

#include "lbind.h"

#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array2OfInteger.hxx>

namespace luaocct {
namespace test {

static void PrintDoubleArray2(const TColStd_Array2OfReal &array2) {
  for (Standard_Integer i = array2.LowerRow(); i <= array2.UpperRow(); ++i) {
    for (Standard_Integer j = array2.LowerCol(); j <= array2.UpperCol(); ++j) {
      std::cout << array2(i, j) << ',';
    }
    std::cout << '\n';
  }
}

static TColStd_Array2OfInteger ReturnIntegerArray2(Standard_Integer u,
                                                   Standard_Integer v) {
  TColStd_Array2OfInteger result{3, u + 2, 2, v + 1};

  for (int i = 1; i <= u; ++i) {
    for (int j = 1; j <= v; ++j) {
      result.SetValue(i + 2, j + 1, i + j);
    }
  }

  return result;
}

} // namespace test
} // namespace luaocct

void luaocct_init_test(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(test)
      .Bind_Method(luaocct::test, PrintDoubleArray2)
      .Bind_Method(luaocct::test, ReturnIntegerArray2)
      .End_Namespace1();
}

#endif
