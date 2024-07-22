#include <lua.hpp>
#include <stdio.h>

int main() {
  printf("Hello, LuaOCCT!\n");

  lua_State *L = luaL_newstate();

  lua_gc(L, LUA_GCSTOP, 0);
  luaL_openlibs(L);
  lua_gc(L, LUA_GCRESTART, -1);

  if (luaL_dofile(L, "../../../src-test/lua/main.lua") != 0) {
    printf("%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);

    return 1;
  }

  return 0;
}
