require("luaocc")

local Geom = LuaOCC.Geom
local gp = LuaOCC.gp
local curveUtil = LuaOCC.util.Curve

local util = require("util")

--------------------------------------------------------------------------------

local test_Geom_Line = util.make_test("Geom_Line", function()
  local ax1 = gp.gp_Ax1(gp.gp.Origin(), gp.gp_Dir(1, 1, 1))
  local a_line = Geom.Geom_Line(ax1)

  util.log("a_line:Value(10) =", a_line:Value(10))
  util.log("a_line.Position_ =", a_line.Position_)
  util.log("a_line:Name() =", a_line:DynamicType():Name())

  util.log("a_line:GetRefCount() =", a_line:GetRefCount())
  util.log("a_line.Length =", curveUtil.GetLength(a_line, -114, 514))
  util.log("a_line:GetRefCount() =", a_line:GetRefCount())
end)

test_invoke_Geom_Line = function(the_line, the_t)
  return the_line:Value(the_t)
end

--------------------------------------------------------------------------------

test_Geom_Line()
