require("luaocc")

local gp = LuaOCC.gp

local util = require("util")

--------------------------------------------------------------------------------

local test_gp_Trsf = util.make_test("gp_Trsf", function()
  local tf = gp.gp_Trsf()

  local axis = gp.gp_Ax1(gp.gp_Pnt(8, 1, 0), gp.gp_Dir(1, 1, 1))
  local angle = math.rad(45)

  tf:SetRotation(axis, angle)

  util.log("tf:GetRotationAxisAngle() =", unpack(tf:GetRotationAxisAngle()))
end)

local test_gp_XYZ = util.make_test("gp_XYZ", function()
  local xyz0 = gp.gp_XYZ(1, 1, 4)
  local xyz1 = gp.gp_XYZ(5, 1, 4)

  util.log("xyz0 * xyz1 =", xyz0 * xyz1)
  util.log("xyz0 * 5 =", xyz0 * 5)
end)

local test_gp_Pnt = util.make_test("gp_Pnt", function()
  local p0 = gp.gp_Pnt(4, 5, 6)
  local p1 = gp.gp_Pnt(1, 1, 1)

  util.log("p0 + p1 =", p0 + p1)
  util.log("p0 - p1 =", p0 - p1)
  util.log("p0 * 3 =", p0 * 3)
  util.log("p1 / 3 =", p1 / 3)
  util.log("-p0 =", -p0)
end)

local test_gp_Pln = util.make_test("gp_Pln", function()
  local the_p = gp.gp_Pnt(3, 4, 5)
  local the_v = gp.gp_Dir(6, 7, 8)
  local a_pln = gp.gp_Pln(the_p, the_v)

  util.log("a_pln:Coefficients() =", a_pln:Coefficients())
  util.log("a_pln.Axis =", a_pln.Axis)
  util.log("a_pln.Location =", a_pln.Location)
  util.log("a_pln.Position =", a_pln.Position)

  a_pln:SetAxis(gp.gp_Ax1(gp.gp_Pnt(0, 9, 9), gp.gp_Dir(1, 1, 1)))
  util.log("a_pln.Axis =", a_pln.Axis.Location, a_pln.Axis.Direction)

  local test_point = gp.gp_Pnt(42, 8, -9.6)
  util.log("a_pln:Distance(test_point) =", a_pln:Distance(test_point))
end)

--------------------------------------------------------------------------------

test_gp_Trsf()
test_gp_XYZ()
test_gp_Pnt()
test_gp_Pln()
