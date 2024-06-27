#include <iostream>
#include <lua.hpp>

int main() {
  std::cout << "Hello, LuaOCCT!\n" << std::endl;

  lua_State *L = luaL_newstate();

  lua_gc(L, LUA_GCSTOP, 0);
  luaL_openlibs(L);
  lua_gc(L, LUA_GCRESTART, -1);

  if (luaL_dofile(L, "../../../src-test/lua/main.lua") != 0) {
    std::cout << lua_tostring(L, -1) << '\n';
    lua_pop(L, 1);

    return 1;
  }

  return 0;
}
