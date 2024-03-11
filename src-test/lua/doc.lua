require("luaocct")

local LODoc = LuaOCCT.LODoc

local util = require("util")

--------------------------------------------------------------------------------

local aDoc = LODoc.LODoc_Document()
aDoc:ImportStep("../../../src-test/stp/geometry.step")
aDoc:DumpXcafDocumentTree()

local e = aDoc:DocumentExplorer(0)
while e:More() do
  print(e:Current().Id)
  e:Next()
end

aDoc:Close()
