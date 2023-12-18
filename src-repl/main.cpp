#include <lua.hpp>

#include <iostream>

int main() {
  std::cout << "Hello, LuaOCC!\n" << std::endl;

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_dofile(L, "../../../src-test/lua/gp.lua") != 0) {
    std::cout << lua_tostring(L, -1) << '\n';
    lua_pop(L, 1);

    return 1;
  }

  return 0;
}
