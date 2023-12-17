#include "luaocc.h"

int init(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("occ")
      .beginNamespace("gp")

      .beginClass<gp_Pnt>("Pnt")
      .addConstructor<void (*)(void)>()
      .addConstructor<void (*)(double, double, double)>()
      .addProperty("x", &gp_Pnt::X, &gp_Pnt::SetX)
      .addProperty("y", &gp_Pnt::Y, &gp_Pnt::SetY)
      .addProperty("z", &gp_Pnt::Z, &gp_Pnt::SetZ)
      .endClass()

      .endNamespace()
      .endNamespace();

  return 0;
}
