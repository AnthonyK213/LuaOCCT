require("luaocct")

local gp_Ax1 = LuaOCCT.gp.gp_Ax1
local gp_Dir = LuaOCCT.gp.gp_Dir
local gp_Pln = LuaOCCT.gp.gp_Pln
local gp_Pnt = LuaOCCT.gp.gp_Pnt
local gp_Quaternion = LuaOCCT.gp.gp_Quaternion
local gp_QuaternionNLerp = LuaOCCT.gp.gp_QuaternionNLerp
local gp_QuaternionSLerp = LuaOCCT.gp.gp_QuaternionSLerp
local gp_Trsf = LuaOCCT.gp.gp_Trsf
local gp_Vec = LuaOCCT.gp.gp_Vec
local gp_XYZ = LuaOCCT.gp.gp_XYZ

local util = require("util")

--------------------------------------------------------------------------------

local test_gp_Trsf = util.make_test("gp_Trsf", function()
  local tf = gp_Trsf()

  local axis = gp_Ax1(gp_Pnt(8, 1, 0), gp_Dir(1, 1, 1))
  local angle = math.rad(45)

  tf:SetRotation(axis, angle)

  util.log("tf:GetRotation() =", tf:GetRotation())
end)

local test_gp_XYZ = util.make_test("gp_XYZ", function()
  local xyz0 = gp_XYZ(1, 1, 4)
  local xyz1 = gp_XYZ(5, 1, 4)

  util.log("xyz0 * xyz1 =", xyz0 * xyz1)
  util.log("xyz0 * 5 =", xyz0 * 5)
end)

local test_gp_Pnt = util.make_test("gp_Pnt", function()
  local p0 = gp_Pnt(4, 5, 6)

  util.log("-p0 =", -p0)
end)

local test_gp_Pln = util.make_test("gp_Pln", function()
  local the_p = gp_Pnt(3, 4, 5)
  local the_v = gp_Dir(6, 7, 8)
  local a_pln = gp_Pln(the_p, the_v)

  util.log("a_pln:Coefficients() =", a_pln:Coefficients())
  util.log("a_pln:Axis()", a_pln:Axis())
  util.log("a_pln:Location()", a_pln:Location())
  util.log("a_pln:Position()", a_pln:Position())

  a_pln:SetAxis(gp_Ax1(gp_Pnt(0, 9, 9), gp_Dir(1, 1, 1)))
  util.log("a_pln:Axis()", a_pln:Axis():Location(), a_pln:Axis():Direction())

  local test_point = gp_Pnt(42, 8, -9.6)
  util.log("a_pln:Distance(test_point) =", a_pln:Distance(test_point))
end)

local test_gp_Quaternion = util.make_test("gp_Quaternion", function()
  local q0 = gp_Quaternion(gp_Vec(1, 1, 4), gp_Vec(5, 1, 4))
  local q1 = gp_Quaternion(gp_Vec(8, 8, 9), gp_Vec(4, 6, 4))

  local nlerp = gp_QuaternionNLerp(q0, q1)
  local qNLerpRes = gp_Quaternion()
  nlerp:Interpolate(0.5, qNLerpRes)
  util.log("nlerp:Interpolate(0.5) =", qNLerpRes)
  util.log("gp_QuaternionNLerp.Interpolate_(q0, q1, 0.5) =", gp_QuaternionNLerp.Interpolate_(q0, q1, 0.5))

  local slerp = gp_QuaternionSLerp(q0, q1)
  local qSLerpRes = gp_Quaternion()
  slerp:Interpolate(0.5, qSLerpRes)
  util.log("slerp:Interpolate(0.5) =", qSLerpRes)
  util.log("gp_QuaternionNLerp.Interpolate_(q0, q1, 0.5) =", gp_QuaternionSLerp.Interpolate_(q0, q1, 0.5))
end)

--------------------------------------------------------------------------------

test_gp_Trsf()
test_gp_XYZ()
test_gp_Pnt()
test_gp_Pln()
test_gp_Quaternion()
