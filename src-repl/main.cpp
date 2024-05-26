#include <lua.hpp>

#include <iostream>

#include <Geom_Line.hxx>

int main() {
  std::cout << "Hello, LuaOCCT!\n" << std::endl;

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_dofile(L, "../../../src-test/lua/main.lua") != 0) {
    std::cout << lua_tostring(L, -1) << '\n';
    lua_pop(L, 1);

    return 1;
  }

  return 0;
}
