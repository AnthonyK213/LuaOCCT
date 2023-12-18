require("luaocc")

local occ = _LuaOCC

local p0 = occ.gp_Pnt(4, 5, 6)
local p1 = occ.gp_Pnt(1, 1, 1)

local p2 = p0 + p1
p2:SetCoord(1, 1, 4)

print(p2)

local v0 = p1 - p0
print(v0)
print(#v0)

v0 = -v0
print(v0)

v0 = v0 / 3
print(v0)

print(occ.gp.Resolution())

local xyz0 = occ.gp_XYZ(1, 1, 4)
local xyz1 = occ.gp_XYZ(5, 1, 4)

local xyz2 = xyz0 * xyz1
print(xyz2)

xyz2 = xyz2 * 3
print(xyz2)

local xyz3 = occ.gp_XYZ()
print(xyz3)
