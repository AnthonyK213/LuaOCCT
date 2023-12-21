#include "luaocc.h"

#include "lAIS.h"
#include "lBRep.h"
#include "lBRepBuilderAPI.h"
#include "lBRepLib.h"
#include "lGeom.h"
#include "lGeomAbs.h"
#include "lStandard.h"
#include "lTopAbs.h"
#include "lTopExp.h"
#include "lTopoDS.h"
#include "lgp.h"

#include "lutil.h"

int32_t luaopen_luaocc(lua_State *L) {
  luaocc_init_Standard(L);

  luaocc_init_BRep(L);
  luaocc_init_BRepBuilderAPI(L);
  luaocc_init_BRepLib(L);
  luaocc_init_Geom(L);
  luaocc_init_GeomAbs(L);
  luaocc_init_TopAbs(L);
  luaocc_init_TopExp(L);
  luaocc_init_TopoDS(L);
  luaocc_init_gp(L);

  luaocc_init_AIS(L);

  luaocc_init_util(L);

  return 0;
}
