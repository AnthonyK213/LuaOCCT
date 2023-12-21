#include "lAIS.h"

int32_t luaocct_init_AIS(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(AIS)

      .End_Namespace1();

  return 0;
}
