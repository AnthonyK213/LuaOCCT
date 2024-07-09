require("luaocct")

local GeomAPI_Interpolate = LuaOCCT.GeomAPI.GeomAPI_Interpolate
local gp_Pnt = LuaOCCT.gp.gp_Pnt

local util = require("util")

--------------------------------------------------------------------------------

local test_GeomAPI_Interpolate = util.make_test("GeomAPI_Interpolate", function()
  local points = {
    gp_Pnt(3, 1, 4),
    gp_Pnt(1, 5, 9),
    gp_Pnt(2, 6, 5),
    gp_Pnt(3, 5, 8),
    gp_Pnt(9, 7, 9),
  }

  local builder = GeomAPI_Interpolate(points, false, 1e-2)
  builder:Perform()

  if builder:IsDone() then
    local curve = builder:Curve()
  end
end)

--------------------------------------------------------------------------------

test_GeomAPI_Interpolate()
