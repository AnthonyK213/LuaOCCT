#include "luaocc.h"

#include "lGeom.h"
#include "lStandard.h"
#include "lTopoDS.h"
#include "lgp.h"

#include "lutil.h"

int32_t luaopen_luaocc(lua_State *L) {
  luaocc_init_Geom(L);
  luaocc_init_TopoDS(L);
  luaocc_init_gp(L);

  luaocc_init_util(L);

  return 0;
}
