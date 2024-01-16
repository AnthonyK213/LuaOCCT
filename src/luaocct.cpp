#include "luaocct.h"

// #include "lBRep.h"
#include "lBRepBuilderAPI.h"
// #include "lBRepLib.h"
#include "lGeom.h"
// #include "lGeomAbs.h"
#include "lGeomConvert.h"
#include "lPoly.h"
#include <lStandard.h>
// #include "lTopAbs.h"
// #include "lTopExp.h"
#include "lTopoDS.h"
#include "lgp.h"

#include "lutil.h"

int32_t luaopen_luaocct(lua_State *L) {
  luaocct_init_Standard(L);

  // luaocct_init_BRep(L);
  luaocct_init_BRepBuilderAPI(L);
  // luaocct_init_BRepLib(L);
  luaocct_init_Geom(L);
  // luaocct_init_GeomAbs(L);
  luaocct_init_GeomConvert(L);
  luaocct_init_Poly(L);
  // luaocct_init_TopAbs(L);
  // luaocct_init_TopExp(L);
  luaocct_init_TopoDS(L);
  luaocct_init_gp(L);

  luaocct_init_util(L);

  return 0;
}
