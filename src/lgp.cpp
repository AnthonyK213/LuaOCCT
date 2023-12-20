#include "lgp.h"

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
      .addFunction("__tostring", [](const T &self) -> std::string {            \
        std::ostringstream oss{};                                              \
        oss << #T << "{ " << self.X() << ", " << self.Y() << ", " << self.Z()  \
            << " }";                                                           \
        return oss.str();                                                      \
      })

int32_t luaocc_init_gp(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace2(gp, gp_TrsfForm)
      .Bind_Enum(gp_TrsfForm, gp_Identity)
      .Bind_Enum(gp_TrsfForm, gp_Rotation)
      .Bind_Enum(gp_TrsfForm, gp_Translation)
      .Bind_Enum(gp_TrsfForm, gp_PntMirror)
      .Bind_Enum(gp_TrsfForm, gp_Ax1Mirror)
      .Bind_Enum(gp_TrsfForm, gp_Ax2Mirror)
      .Bind_Enum(gp_TrsfForm, gp_Scale)
      .Bind_Enum(gp_TrsfForm, gp_CompoundTrsf)
      .Bind_Enum(gp_TrsfForm, gp_Other)
      .End_Namespace2();

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
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
      .Begin_Class(gp_Ax1)
      .addConstructor<void(), void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Property(gp_Ax1, Direction, SetDirection)
      .Bind_Property(gp_Ax1, Location, SetLocation)
      .End_Class()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
      .Begin_Class(gp_Ax2)
      .End_Class()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
      .Begin_Class(gp_Ax3)
      .End_Class()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
      .Begin_Class(gp_Quaternion)
      .End_Class()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
      .Begin_Class(gp_Mat)
      .End_Class()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
      .Begin_Class(gp_Trsf2d)
      .addConstructor<void(), void(const gp_Trsf &)>()
      .End_Class()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
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
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
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
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
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
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
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
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(gp)
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

  return 0;
}

#undef Bind_XYZ
