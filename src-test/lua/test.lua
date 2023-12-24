require("luaocct")

local test = LuaOCCT.test

if not test then
  return
end

local util = require("util")

--------------------------------------------------------------------------------

local test_array2 = util.make_test("test_array2", function()
  local array2 = {
    { 3, 1, 4, 1, 5 },
    { 9, 2, 6, 5, 3 },
    { 5, 8, 9, 7, 9 },
  }

  test.PrintDoubleArray2(array2)

  util.log("test.ReturnIntegerArray2() =", test.ReturnIntegerArray2(6, 4))
end)

--------------------------------------------------------------------------------

test_array2()
