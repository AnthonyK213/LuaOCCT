#include "luaocc.h"

#define LuaBridge__G(L) luabridge::getGlobalNamespace(L)

#define Begin_Namespace() beginNamespace("_LuaOCC")
#define End_Namespace() endNamespace()

#define Begin_Class(T) beginClass<T>(#T)
#define End_Class() endClass()

#define Bind_Property(T, G, S) addProperty(#G, &T::G, &T::S)
#define Bind_Method(T, M) addFunction(#M, &T::M)

int32_t luaocc_init_Geom(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(Geom_Curve)
      .End_Class()
      .End_Namespace();

  return 0;
}

#define Bind_XYZ(T)                                                            \
  addProperty("X", &T::X, &T::SetX)                                            \
      .addProperty("Y", &T::Y, &T::SetY)                                       \
      .addProperty("Z", &T::Z, &T::SetZ)                                       \
      .addFunction(                                                            \
          "SetCoord",                                                          \
          luabridge::overload<Standard_Real, Standard_Real, Standard_Real>(    \
              &T::SetCoord),                                                   \
          luabridge::overload<Standard_Integer, Standard_Real>(&T::SetCoord))  \
      .addFunction("__unm",                                                    \
                   [](const T &self) -> T {                                    \
                     return {-self.X(), -self.Y(), -self.Z()};                 \
                   })                                                          \
      .addFunction("__eq",                                                     \
                   [](const T &self, const T &other) -> bool {                 \
                     return self.X() == other.X() && self.Y() == other.Y() &&  \
                            self.Z() == other.Z();                             \
                   })                                                          \
      .addFunction("__tostring", [](const T &self) -> std::string {            \
        std::ostringstream oss{};                                              \
        oss << #T << "{ " << self.X() << ", " << self.Y() << ", " << self.Z()  \
            << " }";                                                           \
        return oss.str();                                                      \
      })

int32_t luaocc_init_gp(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace()
      .beginNamespace("gp")
      .Bind_Method(gp, Resolution)
      .Bind_Method(gp, Origin)
      .Bind_Method(gp, DX)
      .Bind_Method(gp, DY)
      .Bind_Method(gp, DZ)
      .Bind_Method(gp, OX)
      .Bind_Method(gp, OY)
      .Bind_Method(gp, OZ)
      .Bind_Method(gp, XOY)
      .Bind_Method(gp, YOZ)
      .Bind_Method(gp, ZOX)
      .Bind_Method(gp, Origin2d)
      .Bind_Method(gp, DX2d)
      .Bind_Method(gp, DY2d)
      .Bind_Method(gp, OX2d)
      .Bind_Method(gp, OY2d)
      .endNamespace()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Ax1)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Ax2)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Ax3)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Trsf)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_XYZ)
      .addConstructor<void(),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_XYZ)
      .addFunction("__add", &gp_XYZ::Added)
      .addFunction("__sub", &gp_XYZ::Subtracted)
      .addFunction("__mul",
                   luabridge::overload<const gp_XYZ &>(&gp_XYZ::Multiplied),
                   luabridge::overload<Standard_Real>(&gp_XYZ::Multiplied))
      .addFunction("__div", &gp_XYZ::Divided)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Pnt)
      .addConstructor<void(), void(const gp_XYZ &),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_Pnt)
      .addFunction(
          "__add",
          [](const gp_Pnt &self, const gp_Pnt &other) -> gp_Pnt {
            return self.XYZ() + other.XYZ();
          },
          [](const gp_Pnt &self, const gp_Vec &other) -> gp_Pnt {
            return self.XYZ() + other.XYZ();
          })
      .addFunction(
          "__sub",
          [](const gp_Pnt &self, const gp_Pnt &other) -> gp_Vec {
            return self.XYZ() - other.XYZ();
          },
          [](const gp_Pnt &self, const gp_Vec &other) -> gp_Pnt {
            return self.XYZ() - other.XYZ();
          })
      .addFunction("__mul",
                   [](const gp_Pnt &self, Standard_Real t) -> gp_Pnt {
                     return self.XYZ() * t;
                   })
      .addFunction("__div",
                   [](const gp_Pnt &self, Standard_Real t) -> gp_Pnt {
                     return self.XYZ() / t;
                   })
      .Bind_Method(gp_Pnt, Distance)
      .Bind_Method(gp_Pnt, SquareDistance)
      .Bind_Method(gp_Pnt, Rotate)
      .Bind_Method(gp_Pnt, Rotated)
      .Bind_Method(gp_Pnt, Scale)
      .Bind_Method(gp_Pnt, Scaled)
      .Bind_Method(gp_Pnt, Transform)
      .Bind_Method(gp_Pnt, Transformed)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Vec)
      .addConstructor<void(), void(const gp_Dir &), void(const gp_XYZ &),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_Vec)
      .addFunction("__add", &gp_Vec::Added)
      .addFunction("__sub", &gp_Vec::Subtracted)
      .addFunction("__mul", luabridge::overload<const gp_Vec &>(&gp_Vec::Dot),
                   luabridge::overload<Standard_Real>(&gp_Vec::Multiplied))
      .addFunction("__div", &gp_Vec::Divided)
      .addFunction("__len", &gp_Vec::Magnitude)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Dir)
      .addConstructor<void(), void(const gp_Vec &), void(const gp_XYZ &),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_Dir)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Pln)
      .End_Class()
      .End_Namespace();

  return 0;
}

#undef Bind_XYZ

int32_t luaopen_luaocc(lua_State *L) {
  luaocc_init_Geom(L);
  luaocc_init_gp(L);

  return 0;
}
