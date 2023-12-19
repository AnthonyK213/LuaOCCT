#include <lua.hpp>

#include <LuaBridge/LuaBridge.h>

#include <iostream>

#include <Geom_Line.hxx>

int main() {
  std::cout << "Hello, LuaOCC!\n" << std::endl;

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_dofile(L, "../../../src-test/lua/main.lua") != 0) {
    std::cout << lua_tostring(L, -1) << '\n';
    lua_pop(L, 1);

    return 1;
  }

  gp_Ax1 ax1{gp::Origin(), gp_Dir(1, 1, 1)};
  Handle(Geom_Line) theLine = new Geom_Line(ax1);

  luabridge::LuaRef test_invoke_Geom_Line =
      luabridge::getGlobal(L, "test_invoke_Geom_Line");

  try {
    luabridge::LuaResult result = test_invoke_Geom_Line(theLine.get(), 10);

    if (!result) {
      std::cout << result.errorMessage() << std::endl;
    } else {
      gp_Pnt point = result[0].unsafe_cast<gp_Pnt>();
      std::cout << point.X() << ',' << point.Y() << ',' << point.Z()
                << std::endl;
    }
  } catch (const luabridge::LuaException &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
