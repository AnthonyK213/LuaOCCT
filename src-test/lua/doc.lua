require("luaocct")

local LODoc = LuaOCCT.LODoc
local BRepBuilderAPI_MakeVertex = LuaOCCT.BRepBuilderAPI.BRepBuilderAPI_MakeVertex
local gp_Pnt = LuaOCCT.gp.gp_Pnt
local Poly_Triangulation = LuaOCCT.Poly.Poly_Triangulation

local util = require("util")

--------------------------------------------------------------------------------

local test_import_step = util.make_test("import_step", function()
  local aDoc = LODoc.LODoc_Document()
  aDoc:InitHeadless()
  aDoc:ImportStep("../../../src-test/stp/geometry.step")
  aDoc:DumpXcafDocumentTree()

  local e = aDoc:DocumentExplorer(1)
  while e:More() do
    print(e:Current().Id)
    e:Next()
  end

  aDoc:Close()
end)

local test_add_shape = util.make_test("add_shape", function()
  local aDoc = LODoc.LODoc_Document()
  aDoc:InitHeadless()
  local aLabVert = aDoc:Objects():AddShape(BRepBuilderAPI_MakeVertex(gp_Pnt(1, 2, 3)):Shape(), true)
  local aMesh = Poly_Triangulation()
  local aLabMesh = aDoc:Objects():AddMesh(aMesh, true)

  print(LODoc.LODoc_Attribute.GetName(aLabVert, true))
  print(LODoc.LODoc_Attribute.GetName(aLabMesh, true))

  aDoc:DumpXcafDocumentTree()

  -- aDoc:Objects():SelectObject(aLab, true, true)
  aDoc:Objects():SelectAll(true)
  -- aDoc:Objects():UnselectAll(true)
  print(#aDoc:Objects():SelectedObjects())

  aDoc:Close()
end)

--------------------------------------------------------------------------------

test_import_step()
test_add_shape()
