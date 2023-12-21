require("luaocc")

local BRepBuilderAPI = LuaOCC.BRepBuilderAPI
local BRep = LuaOCC.BRep
local BRepLib = LuaOCC.BRepLib
local Geom = LuaOCC.Geom
local TopoDS = LuaOCC.TopoDS
local gp = LuaOCC.gp

local util = require("util")

--------------------------------------------------------------------------------

local test_TopoDS_Edge = util.make_test("test_TopoDS_Edge", function()
  local p1 = gp.gp_Pnt(1, 1, 4)
  local p2 = gp.gp_Pnt(8, 8, 9)

  local make_edge = BRepBuilderAPI.BRepBuilderAPI_MakeEdge(p1, p2)

  assert(make_edge:IsDone())

  local edge = make_edge:Edge()
  BRepLib.BRepLib.BuildCurves3d(edge)

  local line, first, last = unpack(BRep.BRep_Tool.Curve(edge))

  util.log("Edge line:", line:DynamicType():Name(), first, last)
end)

--------------------------------------------------------------------------------

test_TopoDS_Edge()
