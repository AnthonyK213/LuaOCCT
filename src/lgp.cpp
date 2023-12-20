#include "lgp.h"

static inline void luaocc_init_gp_Enum(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(gp)

      .Begin_Namespace(gp_TrsfForm)
      .Bind_Enum(gp_TrsfForm, gp_Identity)
      .Bind_Enum(gp_TrsfForm, gp_Rotation)
      .Bind_Enum(gp_TrsfForm, gp_Translation)
      .Bind_Enum(gp_TrsfForm, gp_PntMirror)
      .Bind_Enum(gp_TrsfForm, gp_Ax1Mirror)
      .Bind_Enum(gp_TrsfForm, gp_Ax2Mirror)
      .Bind_Enum(gp_TrsfForm, gp_Scale)
      .Bind_Enum(gp_TrsfForm, gp_CompoundTrsf)
      .Bind_Enum(gp_TrsfForm, gp_Other)
      .End_Namespace()

      .Begin_Namespace(gp_EulerSequence)
      .Bind_Enum(gp_EulerSequence, gp_EulerAngles)
      .Bind_Enum(gp_EulerSequence, gp_YawPitchRoll)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_XYZ)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_XZY)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_YZX)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_YXZ)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_ZXY)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_ZYX)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_XYZ)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_XZY)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_YZX)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_YXZ)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_ZXY)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_ZYX)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_XYX)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_XZX)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_YZY)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_YXY)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_ZYZ)
      .Bind_Enum(gp_EulerSequence, gp_Extrinsic_ZXZ)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_XYX)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_XZX)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_YZY)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_YXY)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_ZYZ)
      .Bind_Enum(gp_EulerSequence, gp_Intrinsic_ZXZ)
      .End_Namespace()

      .End_Namespace1();
}

#define Bind_AxN(T)                                                            \
  Bind_Property(T, Direction, SetDirection)                                    \
      .Bind_Property(T, Location, SetLocation)                                 \
      .addFunction("Mirror", luabridge::overload<const gp_Pnt &>(&T::Mirror),  \
                   luabridge::overload<const gp_Ax1 &>(&T::Mirror),            \
                   luabridge::overload<const gp_Ax2 &>(&T::Mirror))            \
      .addFunction("Mirrored",                                                 \
                   luabridge::overload<const gp_Pnt &>(&T::Mirrored),          \
                   luabridge::overload<const gp_Ax1 &>(&T::Mirrored),          \
                   luabridge::overload<const gp_Ax2 &>(&T::Mirrored))          \
      .Bind_Method(T, Rotate)                                                  \
      .Bind_Method(T, Rotated)                                                 \
      .Bind_Method(T, Scale)                                                   \
      .Bind_Method(T, Scaled)                                                  \
      .Bind_Method(T, Transform)                                               \
      .Bind_Method(T, Transformed)                                             \
      .addFunction(                                                            \
          "Translate", luabridge::overload<const gp_Vec &>(&T::Translate),     \
          luabridge::overload<const gp_Pnt &, const gp_Pnt &>(&T::Translate))  \
      .addFunction(                                                            \
          "Translated", luabridge::overload<const gp_Vec &>(&T::Translated),   \
          luabridge::overload<const gp_Pnt &, const gp_Pnt &>(&T::Translated))

static inline void luaocc_init_gp_AxN(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(gp)

      .Begin_Class(gp)
      .Bind_Method_Static(gp, Resolution)
      .Bind_Method_Static(gp, Origin)
      .Bind_Method_Static(gp, DX)
      .Bind_Method_Static(gp, DY)
      .Bind_Method_Static(gp, DZ)
      .Bind_Method_Static(gp, OX)
      .Bind_Method_Static(gp, OY)
      .Bind_Method_Static(gp, OZ)
      .Bind_Method_Static(gp, XOY)
      .Bind_Method_Static(gp, YOZ)
      .Bind_Method_Static(gp, ZOX)
      .Bind_Method_Static(gp, Origin2d)
      .Bind_Method_Static(gp, DX2d)
      .Bind_Method_Static(gp, DY2d)
      .Bind_Method_Static(gp, OX2d)
      .Bind_Method_Static(gp, OY2d)
      .End_Class()

      .Begin_Class(gp_Ax1)
      .addConstructor<void(), void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Method(gp_Ax1, IsCoaxial)
      .Bind_Method(gp_Ax1, IsNormal)
      .Bind_Method(gp_Ax1, IsOpposite)
      .Bind_Method(gp_Ax1, IsParallel)
      .Bind_Method(gp_Ax1, Angle)
      .Bind_Method(gp_Ax1, Reverse)
      .Bind_Method(gp_Ax1, Reversed)
      .Bind_AxN(gp_Ax1)
      .End_Class()

      .Begin_Class(gp_Ax2)
      .addConstructor<void(),
                      void(const gp_Pnt &, const gp_Dir &, const gp_Dir &),
                      void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Property(gp_Ax2, Axis, SetAxis)
      .Bind_Property(gp_Ax2, XDirection, SetXDirection)
      .Bind_Property(gp_Ax2, YDirection, SetYDirection)
      .addFunction(
          "IsCoplanar",
          luabridge::overload<const gp_Ax2 &, const Standard_Real,
                              const Standard_Real>(&gp_Ax2::IsCoplanar),
          luabridge::overload<const gp_Ax1 &, const Standard_Real,
                              const Standard_Real>(&gp_Ax2::IsCoplanar))
      .Bind_AxN(gp_Ax2)
      .End_Class()

      .Begin_Class(gp_Ax3)
      .addConstructor<void(), void(const gp_Ax2 &),
                      void(const gp_Pnt &, const gp_Dir &, const gp_Dir &),
                      void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Property(gp_Ax3, Axis, SetAxis)
      .Bind_Property(gp_Ax3, XDirection, SetXDirection)
      .Bind_Property(gp_Ax3, YDirection, SetYDirection)
      .Bind_Method(gp_Ax3, XReverse)
      .Bind_Method(gp_Ax3, YReverse)
      .Bind_Method(gp_Ax3, ZReverse)
      .Bind_Method(gp_Ax3, Angle)
      .Bind_Method(gp_Ax3, Ax2)
      .addFunction(
          "IsCoplanar",
          luabridge::overload<const gp_Ax3 &, const Standard_Real,
                              const Standard_Real>(&gp_Ax3::IsCoplanar),
          luabridge::overload<const gp_Ax3 &, const Standard_Real,
                              const Standard_Real>(&gp_Ax3::IsCoplanar))
      .Bind_AxN(gp_Ax3)
      .End_Class()

      .End_Namespace1();
}

#undef Bind_AxN

#define Bind_Quaternion_Interpolate(M)                                         \
  Begin_Class(M)                                                               \
      .addConstructor<void(),                                                  \
                      void(const gp_Quaternion &, const gp_Quaternion &)>()    \
      .Bind_Method(M, Init)                                                    \
      .Bind_Method(M, InitFromUnit)                                            \
      .addFunction(                                                            \
          "Interpolate",                                                       \
          +[](const M &self, Standard_Real t) -> gp_Quaternion {               \
            gp_Quaternion result{};                                            \
            self.Interpolate(t, result);                                       \
            return result;                                                     \
          })                                                                   \
      .addStaticFunction(                                                      \
          "Interpolate_",                                                      \
          luabridge::overload<const gp_Quaternion &, const gp_Quaternion &,    \
                              Standard_Real>(&M::Interpolate))                 \
      .End_Class()

static inline void luaocc_init_gp_LA(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(gp)

      .Begin_Class(gp_Quaternion)
      .addConstructor<void(),
                      void(const Standard_Real, const Standard_Real,
                           const Standard_Real, const Standard_Real),
                      void(const gp_Vec &, const gp_Vec &),
                      void(const gp_Vec &, const gp_Vec &, const gp_Vec &),
                      void(const gp_Vec &, const Standard_Real),
                      void(const gp_Mat &)>()
      .Bind_Property_Readonly(gp_Quaternion, X)
      .Bind_Property_Readonly(gp_Quaternion, Y)
      .Bind_Property_Readonly(gp_Quaternion, Z)
      .Bind_Property_Readonly(gp_Quaternion, W)
      .Bind_Method(gp_Quaternion, IsEqual)
      .addFunction(
          "SetRotation",
          luabridge::overload<const gp_Vec &, const gp_Vec &>(
              &gp_Quaternion::SetRotation),
          luabridge::overload<const gp_Vec &, const gp_Vec &, const gp_Vec &>(
              &gp_Quaternion::SetRotation))
      .addFunction(
          "GetVectorAndAngle",
          +[](const gp_Quaternion &self) -> std::tuple<gp_Vec, Standard_Real> {
            gp_Vec axis{};
            Standard_Real angle;
            self.GetVectorAndAngle(axis, angle);
            return {axis, angle};
          })
      .Bind_Method(gp_Quaternion, SetVectorAndAngle)
      .Bind_Method(gp_Quaternion, GetMatrix)
      .Bind_Method(gp_Quaternion, SetMatrix)
      .addFunction(
          "GetEulerAngles",
          +[](const gp_Quaternion &self, const gp_EulerSequence &order)
              -> std::tuple<Standard_Real, Standard_Real, Standard_Real> {
            Standard_Real a, b, c;
            self.GetEulerAngles(order, a, b, c);
            return {a, b, c};
          })
      .Bind_Method(gp_Quaternion, SetEulerAngles)
      .addFunction(
          "Set",
          luabridge::overload<const Standard_Real, const Standard_Real,
                              const Standard_Real, const Standard_Real>(
              &gp_Quaternion::Set),
          luabridge::overload<const gp_Quaternion &>(&gp_Quaternion::Set))
      .Bind_Method(gp_Quaternion, SetIdent)
      .Bind_Method(gp_Quaternion, Reverse)
      .Bind_Method(gp_Quaternion, Reversed)
      .Bind_Method(gp_Quaternion, Invert)
      .Bind_Method(gp_Quaternion, Inverted)
      .Bind_Method(gp_Quaternion, SquareNorm)
      .Bind_Method(gp_Quaternion, Norm)
      .Bind_Method(gp_Quaternion, Scale)
      .Bind_Method(gp_Quaternion, Scaled)
      .Bind_Method(gp_Quaternion, StabilizeLength)
      .Bind_Method(gp_Quaternion, Normalize)
      .Bind_Method(gp_Quaternion, Normalized)
      .Bind_Method(gp_Quaternion, Negated)
      .Bind_Method(gp_Quaternion, Added)
      .Bind_Method(gp_Quaternion, Subtracted)
      .Bind_Method(gp_Quaternion, Multiplied)
      .Bind_Method(gp_Quaternion, Add)
      .Bind_Method(gp_Quaternion, Subtract)
      .addFunction(
          "Multiply",
          luabridge::overload<const gp_Quaternion &>(&gp_Quaternion::Multiply),
          luabridge::overload<const gp_Vec &>(&gp_Quaternion::Multiply))
      .Bind_Method(gp_Quaternion, Dot)
      .Bind_Method(gp_Quaternion, GetRotationAngle)
      .addFunction("__add", &gp_Quaternion::Added)
      .addFunction("__sub", &gp_Quaternion::Subtracted)
      .addFunction("__mul", &gp_Quaternion::Multiplied)
      .addFunction(
          "__tostring",
          +[](const gp_Quaternion &self) -> std::string {
            std::ostringstream oss{};
            oss << "gp_Quaternion{" << self.X() << ',' << self.Y() << ','
                << self.Z() << ',' << self.W() << '}';
            return oss.str();
          })
      .End_Class()

      .Bind_Quaternion_Interpolate(gp_QuaternionNLerp)

      .Bind_Quaternion_Interpolate(gp_QuaternionSLerp)

      .Begin_Class(gp_Mat)
      .addConstructor<
          void(),
          void(const Standard_Real, const Standard_Real, const Standard_Real,
               const Standard_Real, const Standard_Real, const Standard_Real,
               const Standard_Real, const Standard_Real, const Standard_Real),
          void(const gp_XYZ &, const gp_XYZ &, const gp_XYZ &)>()
      .Bind_Method(gp_Mat, SetCol)
      .Bind_Method(gp_Mat, SetCols)
      .Bind_Method(gp_Mat, SetCross)
      .Bind_Method(gp_Mat, SetDiagonal)
      .Bind_Method(gp_Mat, SetDot)
      .Bind_Method(gp_Mat, SetIdentity)
      .Bind_Method(gp_Mat, SetRotation)
      .Bind_Method(gp_Mat, SetRow)
      .Bind_Method(gp_Mat, SetRows)
      .Bind_Method(gp_Mat, SetScale)
      .Bind_Method(gp_Mat, SetValue)
      .Bind_Method(gp_Mat, Column)
      .Bind_Method(gp_Mat, Determinant)
      .Bind_Method(gp_Mat, Diagonal)
      .Bind_Method(gp_Mat, Row)
      .Bind_Method(gp_Mat, Value)
      .Bind_Method(gp_Mat, IsSingular)
      .Bind_Method(gp_Mat, Add)
      .Bind_Method(gp_Mat, Added)
      .Bind_Method(gp_Mat, Divide)
      .Bind_Method(gp_Mat, Divided)
      .Bind_Method(gp_Mat, Invert)
      .Bind_Method(gp_Mat, Inverted)
      .Bind_Method(gp_Mat, PreMultiply)
      .addFunction(
          "Multiplied",
          luabridge::overload<const gp_Mat &>(&gp_Mat::Multiplied),
          luabridge::overload<const Standard_Real>(&gp_Mat::Multiplied))
      .addFunction("Multiply",
                   luabridge::overload<const gp_Mat &>(&gp_Mat::Multiply),
                   luabridge::overload<const Standard_Real>(&gp_Mat::Multiply))
      .Bind_Method(gp_Mat, Power)
      .Bind_Method(gp_Mat, Powered)
      .Bind_Method(gp_Mat, Subtract)
      .Bind_Method(gp_Mat, Subtracted)
      .Bind_Method(gp_Mat, Transpose)
      .Bind_Method(gp_Mat, Transposed)
      .addFunction("__add", &gp_Mat::Added)
      .addFunction("__div", &gp_Mat::Divided)
      .addFunction(
          "__mul", luabridge::overload<const gp_Mat &>(&gp_Mat::Multiplied),
          luabridge::overload<const Standard_Real>(&gp_Mat::Multiplied))
      .addFunction("__sub", &gp_Mat::Subtracted)
      .End_Class()

      .Begin_Class(gp_Trsf2d)
      .addConstructor<void(), void(const gp_Trsf &)>()
      .addFunction("SetMirror",
                   luabridge::overload<const gp_Pnt2d &>(&gp_Trsf2d::SetMirror),
                   luabridge::overload<const gp_Ax2d &>(&gp_Trsf2d::SetMirror))
      .Bind_Method(gp_Trsf2d, SetRotation)
      .Bind_Method(gp_Trsf2d, SetScale)
      .addFunction(
          "SetTransformation",
          luabridge::overload<const gp_Ax2d &, const gp_Ax2d &>(
              &gp_Trsf2d::SetTransformation),
          luabridge::overload<const gp_Ax2d &>(&gp_Trsf2d::SetTransformation))
      .addFunction(
          "SetTranslation",
          luabridge::overload<const gp_Vec2d &>(&gp_Trsf2d::SetTranslation),
          luabridge::overload<const gp_Pnt2d &, const gp_Pnt2d &>(
              &gp_Trsf2d::SetTranslation))
      .Bind_Method(gp_Trsf2d, SetTranslationPart)
      .Bind_Method(gp_Trsf2d, SetScaleFactor)
      .Bind_Method(gp_Trsf2d, IsNegative)
      .Bind_Method(gp_Trsf2d, Form)
      .Bind_Method(gp_Trsf2d, ScaleFactor)
      .Bind_Method(gp_Trsf2d, TranslationPart)
      .Bind_Method(gp_Trsf2d, VectorialPart)
      .Bind_Method(gp_Trsf2d, HVectorialPart)
      .Bind_Method(gp_Trsf2d, RotationPart)
      .Bind_Method(gp_Trsf2d, Value)
      .Bind_Method(gp_Trsf2d, Invert)
      .Bind_Method(gp_Trsf2d, Inverted)
      .Bind_Method(gp_Trsf2d, Multiplied)
      .Bind_Method(gp_Trsf2d, Multiply)
      .Bind_Method(gp_Trsf2d, PreMultiply)
      .Bind_Method(gp_Trsf2d, Power)
      .Bind_Method(gp_Trsf2d, Powered)
      .addFunction(
          "Transforms",
          +[](const gp_Trsf2d &self) -> gp_XY {
            gp_XY xy{};
            self.Transforms(xy);
            return xy;
          })
      .addFunction("__mul", &gp_Trsf2d::Multiplied)
      .End_Class()

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
          +[](const gp_Trsf &self) -> std::tuple<gp_XYZ, Standard_Real> {
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
      .addFunction(
          "Transforms",
          +[](const gp_Trsf &self) -> gp_XYZ {
            gp_XYZ result{};
            self.Transforms(result);
            return result;
          })
      .addFunction("__mul", &gp_Trsf::Multiplied)
      .End_Class()

      .End_Namespace1();
}

#undef Bind_Quaternion_Interpolate

#define Bind_XYZ(T)                                                            \
  Bind_Method(T, IsEqual)                                                      \
      .Bind_Property(T, X, SetX)                                               \
      .Bind_Property(T, Y, SetY)                                               \
      .Bind_Property(T, Z, SetZ)                                               \
      .addFunction(                                                            \
          "SetCoord",                                                          \
          luabridge::overload<Standard_Real, Standard_Real, Standard_Real>(    \
              &T::SetCoord),                                                   \
          luabridge::overload<Standard_Integer, Standard_Real>(&T::SetCoord))  \
      .addFunction(                                                            \
          "__unm",                                                             \
          +[](const T &self) -> T {                                            \
            return {-self.X(), -self.Y(), -self.Z()};                          \
          })                                                                   \
      .addFunction(                                                            \
          "__eq",                                                              \
          +[](const T &self, const T &other) -> bool {                         \
            return self.X() == other.X() && self.Y() == other.Y() &&           \
                   self.Z() == other.Z();                                      \
          })                                                                   \
      .addFunction(                                                            \
          "__tostring", +[](const T &self) -> std::string {                    \
            std::ostringstream oss{};                                          \
            oss << #T << '{' << self.X() << "," << self.Y() << ',' << self.Z() \
                << '}';                                                        \
            return oss.str();                                                  \
          })

static inline void luaocc_init_gp_XYZ(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(gp)

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

      .Begin_Class(gp_Pnt)
      .addConstructor<void(), void(const gp_XYZ &),
                      void(Standard_Real, Standard_Real, Standard_Real)>()
      .Bind_XYZ(gp_Pnt)
      .Bind_Property(gp_Pnt, XYZ, SetXYZ)
      .addFunction(
          "__add",
          +[](const gp_Pnt &self, const gp_Pnt &other) -> gp_Pnt {
            return self.XYZ() + other.XYZ();
          },
          +[](const gp_Pnt &self, const gp_Vec &other) -> gp_Pnt {
            return self.XYZ() + other.XYZ();
          })
      .addFunction(
          "__sub",
          +[](const gp_Pnt &self, const gp_Pnt &other) -> gp_Vec {
            return self.XYZ() - other.XYZ();
          },
          +[](const gp_Pnt &self, const gp_Vec &other) -> gp_Pnt {
            return self.XYZ() - other.XYZ();
          })
      .addFunction(
          "__mul",
          +[](const gp_Pnt &self, Standard_Real t) -> gp_Pnt {
            return self.XYZ() * t;
          })
      .addFunction(
          "__div",
          +[](const gp_Pnt &self, Standard_Real t) -> gp_Pnt {
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

      .End_Namespace1();
}

#undef Bind_XYZ

static inline void luaocc_init_gp_Geom(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(gp)

      .Begin_Class(gp_Pln)
      .addConstructor<void(), void(const gp_Ax3 &),
                      void(const gp_Pnt &, const gp_Dir &),
                      void(const Standard_Real, const Standard_Real,
                           const Standard_Real, const Standard_Real)>()
      .addFunction(
          "Coefficients",
          +[](const gp_Pln &self) -> std::vector<Standard_Real> {
            std::vector<Standard_Real> result(4);
            self.Coefficients(result[0], result[1], result[2], result[3]);
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

      .Begin_Class(gp_Lin)
      .addConstructor<void(), void(const gp_Ax1 &),
                      void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Method(gp_Lin, Reverse)
      .Bind_Method(gp_Lin, Reversed)
      .Bind_Property(gp_Lin, Direction, SetDirection)
      .Bind_Property(gp_Lin, Location, SetLocation)
      .Bind_Property(gp_Lin, Position, SetPosition)
      .Bind_Method(gp_Lin, Angle)
      .Bind_Method(gp_Lin, Contains)
      .addFunction("Distance",
                   luabridge::overload<const gp_Pnt &>(&gp_Lin::Distance),
                   luabridge::overload<const gp_Lin &>(&gp_Lin::Distance))
      .addFunction("SquareDistance",
                   luabridge::overload<const gp_Pnt &>(&gp_Lin::SquareDistance),
                   luabridge::overload<const gp_Lin &>(&gp_Lin::SquareDistance))
      .Bind_Method(gp_Lin, Normal)
      .addFunction("Mirror",
                   luabridge::overload<const gp_Pnt &>(&gp_Lin::Mirror),
                   luabridge::overload<const gp_Ax1 &>(&gp_Lin::Mirror),
                   luabridge::overload<const gp_Ax2 &>(&gp_Lin::Mirror))
      .addFunction("Mirrored",
                   luabridge::overload<const gp_Pnt &>(&gp_Lin::Mirrored),
                   luabridge::overload<const gp_Ax1 &>(&gp_Lin::Mirrored),
                   luabridge::overload<const gp_Ax2 &>(&gp_Lin::Mirrored))
      .Bind_Method(gp_Lin, Rotate)
      .Bind_Method(gp_Lin, Rotated)
      .Bind_Method(gp_Lin, Scale)
      .Bind_Method(gp_Lin, Scaled)
      .Bind_Method(gp_Lin, Transform)
      .Bind_Method(gp_Lin, Transformed)
      .addFunction("Translate",
                   luabridge::overload<const gp_Vec &>(&gp_Lin::Translate),
                   luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
                       &gp_Lin::Translate))
      .addFunction("Translated",
                   luabridge::overload<const gp_Vec &>(&gp_Lin::Translated),
                   luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
                       &gp_Lin::Translated))
      .End_Class()

      .End_Namespace1();
}

int32_t luaocc_init_gp(lua_State *L) {
  luaocc_init_gp_Enum(L);
  luaocc_init_gp_AxN(L);
  luaocc_init_gp_LA(L);
  luaocc_init_gp_XYZ(L);
  luaocc_init_gp_Geom(L);

  return 0;
}
