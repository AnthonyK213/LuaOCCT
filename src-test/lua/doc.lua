require("luaocct")

local LODoc = LuaOCCT.LODoc

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

--------------------------------------------------------------------------------

test_import_step();
