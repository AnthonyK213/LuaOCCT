#include "luaocc.h"

#include "lStandard.h"

#include "lGeom.h"
#include "lTopoDS.h"
#include "lgp.h"

int32_t luaopen_luaocc(lua_State *L) {
  luaocc_init_Geom(L);
  luaocc_init_TopoDS(L);
  luaocc_init_gp(L);

  return 0;
}
