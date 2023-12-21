#include "lGeom.h"

void luaocc_init_Geom(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(Geom)
      .Begin_Derive(Geom_Geometry, Standard_Transient)
      .addFunction("Mirror",
                   luabridge::overload<const gp_Pnt &>(&Geom_Geometry::Mirror),
                   luabridge::overload<const gp_Ax1 &>(&Geom_Geometry::Mirror),
                   luabridge::overload<const gp_Ax2 &>(&Geom_Geometry::Mirror))
      .Bind_Method(Geom_Geometry, Rotate)
      .Bind_Method(Geom_Geometry, Scale)
      .addFunction(
          "Translate",
          luabridge::overload<const gp_Vec &>(&Geom_Geometry::Translate),
          luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
              &Geom_Geometry::Translate))
      .Bind_Method(Geom_Geometry, Transform)
      .addFunction(
          "Mirrored",
          luabridge::overload<const gp_Pnt &>(&Geom_Geometry::Mirrored),
          luabridge::overload<const gp_Ax1 &>(&Geom_Geometry::Mirrored),
          luabridge::overload<const gp_Ax2 &>(&Geom_Geometry::Mirrored))
      .Bind_Method(Geom_Geometry, Rotated)
      .Bind_Method(Geom_Geometry, Scaled)
      .addFunction(
          "Translated",
          luabridge::overload<const gp_Vec &>(&Geom_Geometry::Translated),
          luabridge::overload<const gp_Pnt &, const gp_Pnt &>(
              &Geom_Geometry::Translated))
      .Bind_Method(Geom_Geometry, Transformed)
      .Bind_Method(Geom_Geometry, Copy)
      .End_Derive()

      .Begin_Derive(Geom_Curve, Geom_Geometry)
      .Bind_Method(Geom_Curve, Reverse)
      .Bind_Method(Geom_Curve, ReversedParameter)
      .Bind_Method(Geom_Curve, TransformedParameter)
      .Bind_Method(Geom_Curve, ParametricTransformation)
      .Bind_Method(Geom_Curve, Reversed)
      .Bind_Method(Geom_Curve, FirstParameter)
      .Bind_Method(Geom_Curve, LastParameter)
      .Bind_Method(Geom_Curve, IsClosed)
      .Bind_Method(Geom_Curve, IsPeriodic)
      .Bind_Method(Geom_Curve, Period)
      .Bind_Method(Geom_Curve, Continuity)
      .Bind_Method(Geom_Curve, IsCN)
      .addFunction(
          "D0",
          +[](const Geom_Curve &self, const Standard_Real u) -> gp_Pnt {
            gp_Pnt p{};
            self.D0(u, p);
            return p;
          })
      .addFunction(
          "D1",
          +[](const Geom_Curve &self,
              const Standard_Real u) -> std::tuple<gp_Pnt, gp_Vec> {
            gp_Pnt p{};
            gp_Vec v{};
            self.D1(u, p, v);
            return {p, v};
          })
      .addFunction(
          "D2",
          +[](const Geom_Curve &self,
              const Standard_Real u) -> std::tuple<gp_Pnt, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec v1{};
            gp_Vec v2{};
            self.D2(u, p, v1, v2);
            return {p, v1, v2};
          })
      .addFunction(
          "D3",
          +[](const Geom_Curve &self, const Standard_Real u)
              -> std::tuple<gp_Pnt, gp_Vec, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec v1{};
            gp_Vec v2{};
            gp_Vec v3{};
            self.D3(u, p, v1, v2, v3);
            return {p, v1, v2, v3};
          })
      .Bind_Method(Geom_Curve, DN)
      .Bind_Method(Geom_Curve, Value)
      .End_Derive()

      .Begin_Derive(Geom_BoundedCurve, Geom_Curve)
      .Bind_Method(Geom_BoundedCurve, EndPoint)
      .Bind_Method(Geom_BoundedCurve, StartPoint)
      .End_Derive()

      .Begin_Derive(Geom_BSplineCurve, Geom_BoundedCurve)
      .addConstructorFrom<
          Handle(Geom_BSplineCurve),
          void(const TColgp_Array1OfPnt &, const TColStd_Array1OfReal &,
               const TColStd_Array1OfInteger &, const Standard_Integer,
               const Standard_Boolean),
          void(const TColgp_Array1OfPnt &, const TColStd_Array1OfReal &,
               const TColStd_Array1OfReal &, const TColStd_Array1OfInteger &,
               const Standard_Integer, const Standard_Boolean,
               const Standard_Boolean)>()
      .Bind_Method(Geom_BSplineCurve, IncreaseDegree)
      .addFunction(
          "IncreaseMultiplicity",
          luabridge::overload<const Standard_Integer, const Standard_Integer>(
              &Geom_BSplineCurve::IncreaseMultiplicity),
          luabridge::overload<const Standard_Integer, const Standard_Integer,
                              const Standard_Integer>(
              &Geom_BSplineCurve::IncreaseMultiplicity))
      .Bind_Method(Geom_BSplineCurve, IncrementMultiplicity)
      .Bind_Method(Geom_BSplineCurve, InsertKnot)
      .Bind_Method(Geom_BSplineCurve, InsertKnots)
      .Bind_Method(Geom_BSplineCurve, RemoveKnot)
      .Bind_Method(Geom_BSplineCurve, Segment)
      .addFunction(
          "SetKnot",
          luabridge::overload<const Standard_Integer, const Standard_Real>(
              &Geom_BSplineCurve::SetKnot),
          luabridge::overload<const Standard_Integer, const Standard_Real,
                              const Standard_Integer>(
              &Geom_BSplineCurve::SetKnot))
      .Bind_Method(Geom_BSplineCurve, SetKnots)
      .addFunction(
          "PeriodicNormalization",
          +[](const Geom_BSplineCurve &self) -> Standard_Real {
            Standard_Real u;
            self.PeriodicNormalization(u);
            return u;
          })
      .Bind_Method(Geom_BSplineCurve, SetPeriodic)
      .addFunction(
          "SetOrigin",
          luabridge::overload<const Standard_Integer>(
              &Geom_BSplineCurve::SetOrigin),
          luabridge::overload<const Standard_Real, const Standard_Real>(
              &Geom_BSplineCurve::SetOrigin))
      .addFunction(
          "SetPole",
          luabridge::overload<const Standard_Integer, const gp_Pnt &>(
              &Geom_BSplineCurve::SetPole),
          luabridge::overload<const Standard_Integer, const gp_Pnt &,
                              const Standard_Real>(&Geom_BSplineCurve::SetPole))
      .Bind_Method(Geom_BSplineCurve, SetWeight)
      .addFunction(
          "MovePoint",
          +[](Geom_BSplineCurve &self, const Standard_Real u, const gp_Pnt &p,
              const Standard_Integer index1, const Standard_Integer index2)
              -> std::tuple<Standard_Integer, Standard_Integer> {
            Standard_Integer first, last;
            self.MovePoint(u, p, index1, index2, first, last);
            return {first, last};
          })
      .addFunction(
          "MovePointAndTangent",
          +[](Geom_BSplineCurve &self, const Standard_Real u, const gp_Pnt &p,
              const gp_Vec &tangent, const Standard_Real tolerance,
              const Standard_Integer startingCondition,
              const Standard_Integer endingCondition) -> Standard_Integer {
            Standard_Integer errorStatus;
            self.MovePointAndTangent(u, p, tangent, tolerance,
                                     startingCondition, endingCondition,
                                     errorStatus);
            return errorStatus;
          })
      .Bind_Method(Geom_BSplineCurve, SetNotPeriodic)
      .Bind_Method(Geom_BSplineCurve, IsG1)
      .Bind_Method(Geom_BSplineCurve, IsRational)
      .Bind_Property_Readonly(Geom_BSplineCurve, Degree)
      .Bind_Method(Geom_BSplineCurve, LocalValue)
      .addFunction(
          "LocalD0",
          +[](const Geom_BSplineCurve &self, const Standard_Real u,
              const Standard_Integer fromK1,
              const Standard_Integer toK2) -> gp_Pnt {
            gp_Pnt p{};
            self.LocalD0(u, fromK1, toK2, p);
            return p;
          })
      .addFunction(
          "LocalD1",
          +[](const Geom_BSplineCurve &self, const Standard_Real u,
              const Standard_Integer fromK1,
              const Standard_Integer toK2) -> std::tuple<gp_Pnt, gp_Vec> {
            gp_Pnt p{};
            gp_Vec v1{};
            self.LocalD1(u, fromK1, toK2, p, v1);
            return {p, v1};
          })
      .addFunction(
          "LocalD2",
          +[](const Geom_BSplineCurve &self, const Standard_Real u,
              const Standard_Integer fromK1, const Standard_Integer toK2)
              -> std::tuple<gp_Pnt, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec v1{}, v2{};
            self.LocalD2(u, fromK1, toK2, p, v1, v2);
            return {p, v1, v2};
          })
      .addFunction(
          "LocalD3",
          +[](const Geom_BSplineCurve &self, const Standard_Real u,
              const Standard_Integer fromK1, const Standard_Integer toK2)
              -> std::tuple<gp_Pnt, gp_Vec, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec v1{}, v2{}, v3{};
            self.LocalD3(u, fromK1, toK2, p, v1, v2, v3);
            return {p, v1, v2, v3};
          })
      .Bind_Method(Geom_BSplineCurve, LocalDN)
      .Bind_Method(Geom_BSplineCurve, FirstUKnotIndex)
      .Bind_Method(Geom_BSplineCurve, Knot)
      .addFunction("Knot", luabridge::overload<>(&Geom_BSplineCurve::Knots))
      .addFunction("KnotSequence",
                   luabridge::overload<>(&Geom_BSplineCurve::KnotSequence))
      .Bind_Method(Geom_BSplineCurve, KnotDistribution)
      .Bind_Method(Geom_BSplineCurve, LastUKnotIndex)
      .addFunction(
          "LocateU",
          +[](const Geom_BSplineCurve &self, const Standard_Real u,
              const Standard_Real parametricTolerance,
              const Standard_Boolean withKnotRepetition)
              -> std::tuple<Standard_Integer, Standard_Integer> {
            Standard_Integer i1, i2;
            self.LocateU(u, parametricTolerance, i1, i2, withKnotRepetition);
            return {i1, i2};
          })
      .Bind_Method(Geom_BSplineCurve, Multiplicity)
      .addFunction("Multiplicities",
                   luabridge::overload<>(&Geom_BSplineCurve::Multiplicities))
      .Bind_Property_Readonly(Geom_BSplineCurve, NbKnots)
      .Bind_Property_Readonly(Geom_BSplineCurve, NbPoles)
      .Bind_Method(Geom_BSplineCurve, Pole)
      .addFunction("Poles", luabridge::overload<>(&Geom_BSplineCurve::Poles))
      .Bind_Method(Geom_BSplineCurve, Weight)
      .addFunction("Weights",
                   luabridge::overload<>(&Geom_BSplineCurve::Weights))
      .addFunction(
          "Resolution",
          +[](Geom_BSplineCurve &self,
              const Standard_Real tolerance3d) -> Standard_Real {
            Standard_Real uTolerance;
            self.Resolution(tolerance3d, uTolerance);
            return uTolerance;
          })
      .Bind_Method(Geom_BSplineCurve, IsEqual)
      .End_Derive()

      .Begin_Derive(Geom_Line, Geom_Curve)
      .addConstructorFrom<Handle(Geom_Line), void(const gp_Ax1 &),
                          void(const gp_Lin &),
                          void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Property(Geom_Line, Lin, SetLin)
      .Bind_Property(Geom_Line, Position, SetPosition)
      .Bind_Method(Geom_Line, SetDirection)
      .Bind_Method(Geom_Line, SetLocation)
      .End_Derive()

      .End_Namespace1();
}
