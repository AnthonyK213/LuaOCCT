#include "luaocc.h"

#define LuaBridge__G(L) luabridge::getGlobalNamespace(L)

#define Begin_Namespace() beginNamespace("LuaOCC")
#define End_Namespace() endNamespace()

#define Begin_Class(T) beginClass<T>(#T)
#define End_Class() endClass()

#define Bind_Enum(E, V) addVariable(#V, E::V)

#define Bind_Property(T, G, S)                                                 \
  addProperty(#G, &T::G, &T::S).addFunction(#S, &T::S)
#define Bind_Property_Readonly(T, G) addProperty(#G, &T::G)

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
      .addFunction("SetX", &T::SetX)                                           \
      .addFunction("SetY", &T::SetY)                                           \
      .addFunction("SetZ", &T::SetZ)                                           \
      .addFunction(                                                            \
          "SetCoord",                                                          \
          luabridge::overload<Standard_Real, Standard_Real, Standard_Real>(    \
              &T::SetCoord),                                                   \
          luabridge::overload<Standard_Integer, Standard_Real>(&T::SetCoord))  \
      .addFunction("IsEqual", &T::IsEqual)                                     \
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
      .beginNamespace("gp_TrsfForm")
      .Bind_Enum(gp_TrsfForm, gp_Identity)
      .Bind_Enum(gp_TrsfForm, gp_Rotation)
      .Bind_Enum(gp_TrsfForm, gp_Translation)
      .Bind_Enum(gp_TrsfForm, gp_PntMirror)
      .Bind_Enum(gp_TrsfForm, gp_Ax1Mirror)
      .Bind_Enum(gp_TrsfForm, gp_Ax2Mirror)
      .Bind_Enum(gp_TrsfForm, gp_Scale)
      .Bind_Enum(gp_TrsfForm, gp_CompoundTrsf)
      .Bind_Enum(gp_TrsfForm, gp_Other)
      .endNamespace()
      .End_Namespace();

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
      .addConstructor<void(), void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Property(gp_Ax1, Direction, SetDirection)
      .Bind_Property(gp_Ax1, Location, SetLocation)
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
      .Begin_Class(gp_Quaternion)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Mat)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Trsf2d)
      .addConstructor<void(), void(const gp_Trsf &)>()
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Trsf)
      .addConstructor<void(), void(const gp_Trsf2d &)>()
      .addFunction("SetMirror",
                   luabridge::overload<const gp_Pnt &>(&gp_Trsf::SetMirror),
                   luabridge::overload<const gp_Ax1 &>(&gp_Trsf::SetMirror),
                   luabridge::overload<const gp_Ax2 &>(&gp_Trsf::SetMirror))
      .addFunction(
          "SetRotation",
          luabridge::overload<const gp_Ax1 &, const Standard_Real>(
              &gp_Trsf::SetRotation),
          luabridge::overload<const gp_Quaternion &>(&gp_Trsf::SetRotation))
      .Bind_Method(gp_Trsf, SetRotationPart)
      .Bind_Method(gp_Trsf, SetScale)
      .Bind_Method(gp_Trsf, SetDisplacement)
      .addFunction(
          "SetTransformation",
          luabridge::overload<const gp_Ax3 &, const gp_Ax3 &>(
              &gp_Trsf::SetTransformation),
          luabridge::overload<const gp_Ax3 &>(&gp_Trsf::SetTransformation),
          luabridge::overload<const gp_Quaternion &, const gp_Vec &>(
              &gp_Trsf::SetTransformation))
      .addFunction(
          "SetTranslation",
          luabridge::overload<const gp_Vec &>(&gp_Trsf::SetTranslation),
          luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
              &gp_Trsf::SetTranslation))
      .Bind_Method(gp_Trsf, TranslationPart)
      .Bind_Method(gp_Trsf, SetTranslationPart)
      .Bind_Method(gp_Trsf, ScaleFactor)
      .Bind_Method(gp_Trsf, SetScaleFactor)
      .Bind_Method(gp_Trsf, Form)
      .Bind_Method(gp_Trsf, SetForm)
      .addFunction("GetRotationQuaternion",
                   luabridge::overload<>(&gp_Trsf::GetRotation))
      .addFunction(
          "GetRotationAxisAngle",
          [](const gp_Trsf &self) -> std::tuple<gp_XYZ, Standard_Real> {
            gp_XYZ axis{};
            Standard_Real angle{};
            self.GetRotation(axis, angle);
            return {axis, angle};
          })
      .Bind_Method(gp_Trsf, VectorialPart)
      .Bind_Method(gp_Trsf, HVectorialPart)
      .Bind_Method(gp_Trsf, Value)
      .Bind_Method(gp_Trsf, Invert)
      .Bind_Method(gp_Trsf, Inverted)
      .Bind_Method(gp_Trsf, Multiply)
      .Bind_Method(gp_Trsf, Multiplied)
      .Bind_Method(gp_Trsf, PreMultiply)
      .Bind_Method(gp_Trsf, Power)
      .Bind_Method(gp_Trsf, Powered)
      .addFunction("Transforms",
                   [](const gp_Trsf &self) -> gp_XYZ {
                     gp_XYZ result{};
                     self.Transforms(result);
                     return result;
                   })
      .addFunction("__mul", &gp_Trsf::Multiplied)
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
      .Bind_Method(gp_XYZ, Modulus)
      .Bind_Method(gp_XYZ, SquareModulus)
      .Bind_Method(gp_XYZ, Add)
      .Bind_Method(gp_XYZ, Added)
      .Bind_Method(gp_XYZ, Cross)
      .Bind_Method(gp_XYZ, Crossed)
      .Bind_Method(gp_XYZ, CrossMagnitude)
      .Bind_Method(gp_XYZ, CrossSquareMagnitude)
      .Bind_Method(gp_XYZ, CrossCross)
      .Bind_Method(gp_XYZ, CrossCrossed)
      .Bind_Method(gp_XYZ, Divide)
      .Bind_Method(gp_XYZ, Divided)
      .Bind_Method(gp_XYZ, Dot)
      .Bind_Method(gp_XYZ, DotCross)
      .addFunction("Multiply",
                   luabridge::overload<const Standard_Real>(&gp_XYZ::Multiply),
                   luabridge::overload<const gp_XYZ &>(&gp_XYZ::Multiply),
                   luabridge::overload<const gp_Mat &>(&gp_XYZ::Multiply))
      .addFunction(
          "Multiplied",
          luabridge::overload<const Standard_Real>(&gp_XYZ::Multiplied),
          luabridge::overload<const gp_XYZ &>(&gp_XYZ::Multiplied),
          luabridge::overload<const gp_Mat &>(&gp_XYZ::Multiplied))
      .Bind_Method(gp_XYZ, Normalize)
      .Bind_Method(gp_XYZ, Normalized)
      .Bind_Method(gp_XYZ, Reverse)
      .Bind_Method(gp_XYZ, Reversed)
      .Bind_Method(gp_XYZ, Subtract)
      .Bind_Method(gp_XYZ, Subtracted)
      .addFunction("SetLinearForm",
                   luabridge::overload<const gp_XYZ &, const gp_XYZ &>(
                       &gp_XYZ::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_XYZ &,
                                       const gp_XYZ &>(&gp_XYZ::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_XYZ &,
                                       const Standard_Real, const gp_XYZ &>(
                       &gp_XYZ::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_XYZ &,
                                       const Standard_Real, const gp_XYZ &,
                                       const gp_XYZ &>(&gp_XYZ::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_XYZ &,
                                       const Standard_Real, const gp_XYZ &,
                                       const Standard_Real, const gp_XYZ &>(
                       &gp_XYZ::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_XYZ &,
                                       const Standard_Real, const gp_XYZ &,
                                       const Standard_Real, const gp_XYZ &,
                                       const gp_XYZ &>(&gp_XYZ::SetLinearForm))
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Pnt)
      .addConstructor<void(), void(const gp_XYZ &),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_Pnt)
      .Bind_Property(gp_Pnt, XYZ, SetXYZ)
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
      .Bind_Method(gp_Pnt, BaryCenter)
      .Bind_Method(gp_Pnt, Distance)
      .Bind_Method(gp_Pnt, SquareDistance)
      .addFunction("Mirror",
                   luabridge::overload<const gp_Pnt &>(&gp_Pnt::Mirror),
                   luabridge::overload<const gp_Ax1 &>(&gp_Pnt::Mirror),
                   luabridge::overload<const gp_Ax2 &>(&gp_Pnt::Mirror))
      .addFunction("Mirrored",
                   luabridge::overload<const gp_Pnt &>(&gp_Pnt::Mirrored),
                   luabridge::overload<const gp_Ax1 &>(&gp_Pnt::Mirrored),
                   luabridge::overload<const gp_Ax2 &>(&gp_Pnt::Mirrored))
      .Bind_Method(gp_Pnt, Rotate)
      .Bind_Method(gp_Pnt, Rotated)
      .Bind_Method(gp_Pnt, Scale)
      .Bind_Method(gp_Pnt, Scaled)
      .Bind_Method(gp_Pnt, Transform)
      .Bind_Method(gp_Pnt, Transformed)
      .addFunction("Translate",
                   luabridge::overload<const gp_Vec &>(&gp_Pnt::Translate),
                   luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
                       &gp_Pnt::Translate))
      .addFunction("Translated",
                   luabridge::overload<const gp_Vec &>(&gp_Pnt::Translated),
                   luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
                       &gp_Pnt::Translated))
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Vec)
      .addConstructor<void(), void(const gp_Dir &), void(const gp_XYZ &),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_Vec)
      .Bind_Property(gp_Vec, XYZ, SetXYZ)
      .addFunction("__add", &gp_Vec::Added)
      .addFunction("__sub", &gp_Vec::Subtracted)
      .addFunction("__mul", luabridge::overload<const gp_Vec &>(&gp_Vec::Dot),
                   luabridge::overload<Standard_Real>(&gp_Vec::Multiplied))
      .addFunction("__div", &gp_Vec::Divided)
      .addFunction("__len", &gp_Vec::Magnitude)
      .Bind_Method(gp_Vec, IsNormal)
      .Bind_Method(gp_Vec, IsOpposite)
      .Bind_Method(gp_Vec, IsParallel)
      .Bind_Method(gp_Vec, Angle)
      .Bind_Method(gp_Vec, AngleWithRef)
      .Bind_Method(gp_Vec, Magnitude)
      .Bind_Method(gp_Vec, SquareMagnitude)
      .Bind_Method(gp_Vec, Add)
      .Bind_Method(gp_Vec, Added)
      .Bind_Method(gp_Vec, Subtract)
      .Bind_Method(gp_Vec, Subtracted)
      .Bind_Method(gp_Vec, Multiply)
      .Bind_Method(gp_Vec, Multiplied)
      .Bind_Method(gp_Vec, Divide)
      .Bind_Method(gp_Vec, Divided)
      .Bind_Method(gp_Vec, Cross)
      .Bind_Method(gp_Vec, Crossed)
      .Bind_Method(gp_Vec, CrossMagnitude)
      .Bind_Method(gp_Vec, CrossSquareMagnitude)
      .Bind_Method(gp_Vec, CrossCross)
      .Bind_Method(gp_Vec, CrossCrossed)
      .Bind_Method(gp_Vec, Dot)
      .Bind_Method(gp_Vec, DotCross)
      .Bind_Method(gp_Vec, Normalize)
      .Bind_Method(gp_Vec, Normalized)
      .Bind_Method(gp_Vec, Reverse)
      .Bind_Method(gp_Vec, Reversed)
      .addFunction("SetLinearForm",
                   luabridge::overload<const gp_Vec &, const gp_Vec &>(
                       &gp_Vec::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_Vec &,
                                       const gp_Vec &>(&gp_Vec::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_Vec &,
                                       const Standard_Real, const gp_Vec &>(
                       &gp_Vec::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_Vec &,
                                       const Standard_Real, const gp_Vec &,
                                       const gp_Vec &>(&gp_Vec::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_Vec &,
                                       const Standard_Real, const gp_Vec &,
                                       const Standard_Real, const gp_Vec &>(
                       &gp_Vec::SetLinearForm),
                   luabridge::overload<const Standard_Real, const gp_Vec &,
                                       const Standard_Real, const gp_Vec &,
                                       const Standard_Real, const gp_Vec &,
                                       const gp_Vec &>(&gp_Vec::SetLinearForm))
      .addFunction("Mirror",
                   luabridge::overload<const gp_Vec &>(&gp_Vec::Mirror),
                   luabridge::overload<const gp_Ax1 &>(&gp_Vec::Mirror),
                   luabridge::overload<const gp_Ax2 &>(&gp_Vec::Mirror))
      .addFunction("Mirrored",
                   luabridge::overload<const gp_Vec &>(&gp_Vec::Mirrored),
                   luabridge::overload<const gp_Ax1 &>(&gp_Vec::Mirrored),
                   luabridge::overload<const gp_Ax2 &>(&gp_Vec::Mirrored))
      .Bind_Method(gp_Vec, Rotate)
      .Bind_Method(gp_Vec, Rotated)
      .Bind_Method(gp_Vec, Scale)
      .Bind_Method(gp_Vec, Scaled)
      .Bind_Method(gp_Vec, Transform)
      .Bind_Method(gp_Vec, Transformed)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Dir)
      .addConstructor<void(), void(const gp_Vec &), void(const gp_XYZ &),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_Dir)
      .Bind_Property(gp_Dir, XYZ, SetXYZ)
      .Bind_Method(gp_Dir, IsNormal)
      .Bind_Method(gp_Dir, IsOpposite)
      .Bind_Method(gp_Dir, IsParallel)
      .Bind_Method(gp_Dir, Angle)
      .Bind_Method(gp_Dir, AngleWithRef)
      .Bind_Method(gp_Dir, Cross)
      .Bind_Method(gp_Dir, Crossed)
      .Bind_Method(gp_Dir, CrossCross)
      .Bind_Method(gp_Dir, CrossCrossed)
      .Bind_Method(gp_Dir, Dot)
      .Bind_Method(gp_Dir, DotCross)
      .Bind_Method(gp_Dir, Reverse)
      .Bind_Method(gp_Dir, Reversed)
      .addFunction("Mirror",
                   luabridge::overload<const gp_Dir &>(&gp_Dir::Mirror),
                   luabridge::overload<const gp_Ax1 &>(&gp_Dir::Mirror),
                   luabridge::overload<const gp_Ax2 &>(&gp_Dir::Mirror))
      .addFunction("Mirrored",
                   luabridge::overload<const gp_Dir &>(&gp_Dir::Mirrored),
                   luabridge::overload<const gp_Ax1 &>(&gp_Dir::Mirrored),
                   luabridge::overload<const gp_Ax2 &>(&gp_Dir::Mirrored))
      .Bind_Method(gp_Dir, Rotate)
      .Bind_Method(gp_Dir, Rotated)
      .Bind_Method(gp_Dir, Transform)
      .Bind_Method(gp_Dir, Transformed)
      .End_Class()
      .End_Namespace();

  LuaBridge__G(L)
      .Begin_Namespace()
      .Begin_Class(gp_Pln)
      .addConstructor<void(), void(const gp_Ax3 &),
                      void(const gp_Pnt &, const gp_Dir &),
                      void(const Standard_Real, const Standard_Real,
                           const Standard_Real, const Standard_Real)>()
      .addFunction("Coefficients",
                   [](const gp_Pln &self) -> std::vector<Standard_Real> {
                     std::vector<Standard_Real> result(4);
                     self.Coefficients(result[0], result[1], result[2],
                                       result[3]);
                     return result;
                   })
      .Bind_Property(gp_Pln, Axis, SetAxis)
      .Bind_Property(gp_Pln, Location, SetLocation)
      .Bind_Property(gp_Pln, Position, SetPosition)
      .Bind_Property_Readonly(gp_Pln, XAxis)
      .Bind_Property_Readonly(gp_Pln, YAxis)
      .Bind_Property_Readonly(gp_Pln, Direct)
      .Bind_Method(gp_Pln, UReverse)
      .Bind_Method(gp_Pln, VReverse)
      .addFunction("Distance",
                   luabridge::overload<const gp_Pnt &>(&gp_Pln::Distance),
                   luabridge::overload<const gp_Lin &>(&gp_Pln::Distance),
                   luabridge::overload<const gp_Pln &>(&gp_Pln::Distance))
      .addFunction("SquareDistance",
                   luabridge::overload<const gp_Pnt &>(&gp_Pln::SquareDistance),
                   luabridge::overload<const gp_Lin &>(&gp_Pln::SquareDistance),
                   luabridge::overload<const gp_Pln &>(&gp_Pln::SquareDistance))
      .addFunction("Contains",
                   luabridge::overload<const gp_Pnt &, const Standard_Real>(
                       &gp_Pln::Contains),
                   luabridge::overload<const gp_Lin &, const Standard_Real,
                                       const Standard_Real>(&gp_Pln::Contains))
      .addFunction("Mirror",
                   luabridge::overload<const gp_Pnt &>(&gp_Pln::Mirror),
                   luabridge::overload<const gp_Ax1 &>(&gp_Pln::Mirror),
                   luabridge::overload<const gp_Ax2 &>(&gp_Pln::Mirror))
      .addFunction("Mirrored",
                   luabridge::overload<const gp_Pnt &>(&gp_Pln::Mirrored),
                   luabridge::overload<const gp_Ax1 &>(&gp_Pln::Mirrored),
                   luabridge::overload<const gp_Ax2 &>(&gp_Pln::Mirrored))
      .Bind_Method(gp_Pln, Rotate)
      .Bind_Method(gp_Pln, Rotated)
      .Bind_Method(gp_Pln, Scale)
      .Bind_Method(gp_Pln, Scaled)
      .Bind_Method(gp_Pln, Transform)
      .Bind_Method(gp_Pln, Transformed)
      .addFunction("Translate",
                   luabridge::overload<const gp_Vec &>(&gp_Pln::Translate),
                   luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
                       &gp_Pln::Translate))
      .addFunction("Translated",
                   luabridge::overload<const gp_Vec &>(&gp_Pln::Translated),
                   luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
                       &gp_Pln::Translated))
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
