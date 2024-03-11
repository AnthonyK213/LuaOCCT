require("luaocct")

local BRepBuilderAPI = LuaOCCT.BRepBuilderAPI
local BRep = LuaOCCT.BRep
local BRepLib = LuaOCCT.BRepLib
local Geom = LuaOCCT.Geom
local TopoDS = LuaOCCT.TopoDS
local gp = LuaOCCT.gp

local util = require("util")

--------------------------------------------------------------------------------

local test_TopoDS_Edge = util.make_test("test_TopoDS_Edge", function()
  local p1 = gp.gp_Pnt(1, 1, 4)
  local p2 = gp.gp_Pnt(8, 8, 9)

  local make_edge = BRepBuilderAPI.BRepBuilderAPI_MakeEdge(p1, p2)

  assert(make_edge:IsDone())

  local edge = make_edge:Edge()
  BRepLib.BRepLib.BuildCurves3d(edge)

  local line --[[@type Geom_Curve]], first, last = unpack(BRep.BRep_Tool.Curve(edge))

  util.log("Edge line:", line:DynamicType():Name(), first, last)
end)

--------------------------------------------------------------------------------

test_TopoDS_Edge()
