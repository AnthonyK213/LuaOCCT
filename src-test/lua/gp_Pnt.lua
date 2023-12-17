package.loadlib("../../build/src/Debug/libluaocc.so", "init")()

local point = occ.gp.Pnt(4, 5, 6)
print(point.x)
print(point.y)
print(point.z)

point.y = 10
print(point.x)
print(point.y)
print(point.z)
