require("luaocc")
local occ = LuaOCC

package.path = "../../../src-test/lua/inspect.lua;" .. package.path
local inspect = require("inspect")
local log = function(...)
  local result = ""
  local nb_args = select("#", ...)

  for i = 1, nb_args, 1 do
    local arg = select(i, ...)

    if i == 1 and type(arg) == "string" then
      result = result .. arg
    elseif type(arg) == "userdata" then
      result = result .. " " .. tostring(arg)
    else
      result = result .. " " .. inspect(arg)
    end
  end

  print(result)
end

local function sep(label, new_line)
  local count = math.max(0, 80 - label:len())
  print(label .. string.rep("-", count) .. (new_line and "\n" or ""))
end

local function make_test(name, func)
  return function()
    sep("test_" .. name .. "_begin")
    func()
    sep("test_" .. name .. "_end", true)
  end
end

--------------------------------------------------------------------------------

local test_gp_Trsf = make_test("gp_Trsf", function()
  local tf = occ.gp_Trsf()

  local axis = occ.gp_Ax1(occ.gp_Pnt(8, 1, 0), occ.gp_Dir(1, 1, 1))
  local angle = math.rad(45)

  tf:SetRotation(axis, angle)

  log("tf.GetRotationAxisAngle =", unpack(tf:GetRotationAxisAngle()))
end)

local test_gp_XYZ = make_test("gp_XYZ", function()
  local xyz0 = occ.gp_XYZ(1, 1, 4)
  local xyz1 = occ.gp_XYZ(5, 1, 4)

  log("xyz0 * xyz1 =", xyz0 * xyz1)
  log("xyz0 * 5 =", xyz0 * 5)
end)

local test_gp_Pnt = make_test("gp_Pnt", function()
  local p0 = occ.gp_Pnt(4, 5, 6)
  local p1 = occ.gp_Pnt(1, 1, 1)

  log("p0 + p1 =", p0 + p1)
  log("p0 - p1 =", p0 - p1)
  log("p0 * 3 =", p0 * 3)
  log("p1 / 3 =", p1 / 3)
  log("-p0 =", -p0)
end)

local test_gp_Pln = make_test("gp_Pln", function()
  local the_p = occ.gp_Pnt(3, 4, 5)
  local the_v = occ.gp_Dir(6, 7, 8)
  local a_pln = occ.gp_Pln(the_p, the_v)

  log("a_pln:Coefficients() =", a_pln:Coefficients())
  log("a_pln.Axis =", a_pln.Axis)
  log("a_pln.Location =", a_pln.Location)
  log("a_pln.Position =", a_pln.Position)

  a_pln:SetAxis(occ.gp_Ax1(occ.gp_Pnt(0, 9, 9), occ.gp_Dir(1, 1, 1)))
  log("a_pln.Axis =", a_pln.Axis.Location, a_pln.Axis.Direction)
end)

--------------------------------------------------------------------------------

test_gp_Trsf()
test_gp_XYZ()
test_gp_Pnt()
test_gp_Pln()
