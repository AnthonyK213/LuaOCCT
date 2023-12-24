require("luaocct")

local Geom = LuaOCCT.Geom
local gp = LuaOCCT.gp
local curveUtil = LuaOCCT.util.Curve
local GeomConvert = LuaOCCT.GeomConvert

local util = require("util")

--------------------------------------------------------------------------------

local test_Geom_Line = util.make_test("Geom_Line", function()
  local ax1 = gp.gp_Ax1(gp.gp.Origin(), gp.gp_Dir(1, 1, 1))
  local a_line = Geom.Geom_Line(ax1)

  util.log("a_line:Value(10) =", a_line:Value(10))
  util.log("a_line.Position_ =", a_line.Position_)
  util.log("a_line:DynamicType():Name() =", a_line:DynamicType():Name())

  util.log("a_line:GetRefCount() =", a_line:GetRefCount())
  util.log("a_line.Length =", curveUtil.GetLength(a_line, -114, 514))
  util.log("a_line:GetRefCount() =", a_line:GetRefCount())
end)

local test_Geom_BSplineCurve = util.make_test("Geom_BSplineCurve", function()
  local poles          = { gp.gp_Pnt(1, 0, 0), gp.gp_Pnt(1, 1, 0), gp.gp_Pnt(0, 1, 0) }
  local weights        = { 1, math.sqrt(0.5), 1 }
  local knots          = { 0, 1 }
  local multiplicities = { 3, 3 }
  local degree         = 2
  local periodic       = false
  local check_rational = true


  local a_nurbs = Geom.Geom_BSplineCurve(poles, weights, knots, multiplicities, degree, periodic, check_rational)

  util.log("a_nurbs:DynamicType():Name() =", a_nurbs:DynamicType():Name())
  util.log("a_nurbs:Degree() =", a_nurbs:Degree())
  util.log("a_nurbs.Length =", curveUtil.GetLength(a_nurbs))
  util.log("a_nurbs.Mid =", a_nurbs:Value(0.5))
  util.log("a_nurbs.NbPoles_ =", a_nurbs.NbPoles_)
  util.log("a_nurbs.NbKnots_ =", a_nurbs.NbKnots_)
  util.log("a_nurbs:Poles() =", a_nurbs:Poles())
  util.log("a_nurbs:KnotSequence() =", a_nurbs:KnotSequence())
  util.log("a_nurbs:Multiplicities() =", a_nurbs:Multiplicities())
  util.log("a_nurbs:Weights() =", a_nurbs:Weights())
  util.log("a_nurbs:Resolution(0.5) =", a_nurbs:Resolution(0.5))
  util.log("a_nurbs.StartPoint_ =", a_nurbs.StartPoint_)
  util.log("a_nurbs.EndPoint_ =", a_nurbs.EndPoint_)
  util.log("a_nurbs.FirstParameter_ =", a_nurbs.FirstParameter_)
  util.log("a_nurbs.LastParameter_ =", a_nurbs.LastParameter_)

  local poles1             = { gp.gp_Pnt(0, 1, 0), gp.gp_Pnt(-1, 1, 0), gp.gp_Pnt(-1, 0, 0) }
  local a_nurbs1           = Geom.Geom_BSplineCurve(poles1, weights, knots, multiplicities, degree, periodic,
    check_rational)

  local poles2             = { gp.gp_Pnt(-1, 0, 0), gp.gp_Pnt(-1, -1, 0), gp.gp_Pnt(0, -1, 0) }
  local a_nurbs2           = Geom.Geom_BSplineCurve(poles2, weights, knots, multiplicities, degree, periodic,
    check_rational)

  local poles3             = { gp.gp_Pnt(0, -1, 0), gp.gp_Pnt(1, -1, 0), gp.gp_Pnt(1, 0, 0) }
  local a_nurbs3           = Geom.Geom_BSplineCurve(poles3, weights, knots, multiplicities, degree, periodic,
    check_rational)

  local tol                = 0.1

  local result, closedFlag = unpack(GeomConvert.GeomConvert.ConcatG1({ a_nurbs, a_nurbs1, a_nurbs2, a_nurbs3 },
    { tol, tol, tol },
    true, tol))

  util.log("GeomConvert.ConcatG1: ", result, closedFlag)

  local a_nurbs_copy = a_nurbs:Copy()
  assert(a_nurbs_copy:IsKind("Geom_BSplineCurve"))
  assert(a_nurbs_copy:IsKind(result[1]:DynamicType()))

  local a_nurbs_copy_downcast = Geom.Geom_BSplineCurve.DownCast(a_nurbs_copy)

  util.log("a_nurbs_copy:GetRefCount() =", a_nurbs_copy:GetRefCount())
  util.log("a_nurbs_copy_downcast:GetRefCount() =", a_nurbs_copy_downcast:GetRefCount())

  util.log("a_nurbs_copy_downcast.Length =", curveUtil.GetLength(a_nurbs_copy_downcast))
end)

--------------------------------------------------------------------------------

test_Geom_Line()
test_Geom_BSplineCurve()
