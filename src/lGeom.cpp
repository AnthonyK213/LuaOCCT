#include "lGeom.h"

static inline void luaocct_init_Geom_Curve(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(Geom)

      .Begin_Derive(Geom_Curve, Geom_Geometry)
      .Bind_Method(Geom_Curve, Reverse)
      .Bind_Method(Geom_Curve, ReversedParameter)
      .Bind_Method(Geom_Curve, TransformedParameter)
      .Bind_Method(Geom_Curve, ParametricTransformation)
      .Bind_Method(Geom_Curve, Reversed)
      .Bind_Property_Readonly(Geom_Curve, FirstParameter)
      .Bind_Property_Readonly(Geom_Curve, LastParameter)
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
            gp_Vec v1{}, v2{};
            self.D2(u, p, v1, v2);
            return {p, v1, v2};
          })
      .addFunction(
          "D3",
          +[](const Geom_Curve &self, const Standard_Real u)
              -> std::tuple<gp_Pnt, gp_Vec, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec v1{}, v2{}, v3{};
            self.D3(u, p, v1, v2, v3);
            return {p, v1, v2, v3};
          })
      .Bind_Method(Geom_Curve, DN)
      .Bind_Method(Geom_Curve, Value)
      .Bind_DownCast(Geom_Curve)
      .End_Derive()

      .Begin_Derive(Geom_BoundedCurve, Geom_Curve)
      .Bind_Property_Readonly(Geom_BoundedCurve, EndPoint)
      .Bind_Property_Readonly(Geom_BoundedCurve, StartPoint)
      .Bind_DownCast(Geom_BoundedCurve)
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
      .Bind_DownCast(Geom_BSplineCurve)
      .End_Derive()

      .Begin_Derive(Geom_BezierCurve, Geom_BoundedCurve)
      .addConstructorFrom<
          Handle(Geom_BezierCurve), void(const TColgp_Array1OfPnt &),
          void(const TColgp_Array1OfPnt &, const TColStd_Array1OfReal &)>()
      .Bind_Method(Geom_BezierCurve, Increase)
      .addFunction("InsertPoleAfter",
                   luabridge::overload<const Standard_Integer, const gp_Pnt &>(
                       &Geom_BezierCurve::InsertPoleAfter),
                   luabridge::overload<const Standard_Integer, const gp_Pnt &,
                                       const Standard_Real>(
                       &Geom_BezierCurve::InsertPoleAfter))
      .addFunction("InsertPoleBefore",
                   luabridge::overload<const Standard_Integer, const gp_Pnt &>(
                       &Geom_BezierCurve::InsertPoleBefore),
                   luabridge::overload<const Standard_Integer, const gp_Pnt &,
                                       const Standard_Real>(
                       &Geom_BezierCurve::InsertPoleBefore))
      .Bind_Method(Geom_BezierCurve, RemovePole)
      .Bind_Method(Geom_BezierCurve, Segment)
      .addFunction(
          "SetPole",
          luabridge::overload<const Standard_Integer, const gp_Pnt &>(
              &Geom_BezierCurve::SetPole),
          luabridge::overload<const Standard_Integer, const gp_Pnt &,
                              const Standard_Real>(&Geom_BezierCurve::SetPole))
      .Bind_Method(Geom_BezierCurve, SetWeight)
      .Bind_Property_Readonly(Geom_BezierCurve, Degree)
      .Bind_Property_Readonly(Geom_BezierCurve, NbPoles)
      .Bind_Method(Geom_BezierCurve, Pole)
      .addFunction("Poles", luabridge::overload<>(&Geom_BezierCurve::Poles))
      .Bind_Method(Geom_BezierCurve, Weight)
      .addFunction("Weights", luabridge::overload<>(&Geom_BezierCurve::Weights))
      .addFunction(
          "Resolution",
          +[](Geom_BezierCurve &self,
              const Standard_Real tolerance3d) -> Standard_Real {
            Standard_Real uTolerance;
            self.Resolution(tolerance3d, uTolerance);
            return uTolerance;
          })
      .Bind_DownCast(Geom_BezierCurve)
      .End_Derive()

      .Begin_Derive(Geom_TrimmedCurve, Geom_BoundedCurve)
      .addConstructorFrom<Handle(Geom_TrimmedCurve),
                          void(const Handle(Geom_Curve) &, const Standard_Real,
                               const Standard_Real, const Standard_Boolean,
                               const Standard_Boolean)>()
      .Bind_Method(Geom_TrimmedCurve, SetTrim)
      .Bind_Property_Readonly(Geom_TrimmedCurve, BasisCurve)
      .Bind_DownCast(Geom_TrimmedCurve)
      .End_Derive()

      .Begin_Derive(Geom_Conic, Geom_Curve)
      .Bind_Property(Geom_Conic, Axis, SetAxis)
      .Bind_Property(Geom_Conic, Location, SetLocation)
      .Bind_Property(Geom_Conic, Position, SetPosition)
      .Bind_Property_Readonly(Geom_Conic, Eccentricity)
      .Bind_Property_Readonly(Geom_Conic, XAxis)
      .Bind_Property_Readonly(Geom_Conic, YAxis)
      .Bind_DownCast(Geom_Conic)
      .End_Derive()

      .Begin_Derive(Geom_Circle, Geom_Conic)
      .addConstructorFrom<Handle(Geom_Circle), void(const gp_Circ &),
                          void(const gp_Ax2 &, const Standard_Real)>()
      .Bind_Property(Geom_Circle, Circ, SetCirc)
      .Bind_Property(Geom_Circle, Radius, SetRadius)
      .Bind_DownCast(Geom_Circle)
      .End_Derive()

      .Begin_Derive(Geom_Ellipse, Geom_Conic)
      .addConstructorFrom<Handle(Geom_Ellipse), void(const gp_Elips &),
                          void(const gp_Ax2 &, const Standard_Real,
                               const Standard_Real)>()
      .Bind_Property(Geom_Ellipse, Elips, SetElips)
      .Bind_Property(Geom_Ellipse, MajorRadius, SetMajorRadius)
      .Bind_Property(Geom_Ellipse, MinorRadius, SetMinorRadius)
      .Bind_Property_Readonly(Geom_Ellipse, Directrix1)
      .Bind_Property_Readonly(Geom_Ellipse, Directrix2)
      .Bind_Property_Readonly(Geom_Ellipse, Focal)
      .Bind_Property_Readonly(Geom_Ellipse, Focus1)
      .Bind_Property_Readonly(Geom_Ellipse, Focus2)
      .Bind_Property_Readonly(Geom_Ellipse, Parameter)
      .Bind_DownCast(Geom_Ellipse)
      .End_Derive()

      .Begin_Derive(Geom_Hyperbola, Geom_Conic)
      .addConstructorFrom<Handle(Geom_Hyperbola), void(const gp_Hypr &),
                          void(const gp_Ax2 &, const Standard_Real,
                               const Standard_Real)>()
      .Bind_Property(Geom_Hyperbola, Hypr, SetHypr)
      .Bind_Property(Geom_Hyperbola, MajorRadius, SetMajorRadius)
      .Bind_Property(Geom_Hyperbola, MinorRadius, SetMinorRadius)
      .Bind_Property_Readonly(Geom_Hyperbola, Asymptote1)
      .Bind_Property_Readonly(Geom_Hyperbola, Asymptote2)
      .Bind_Property_Readonly(Geom_Hyperbola, ConjugateBranch1)
      .Bind_Property_Readonly(Geom_Hyperbola, ConjugateBranch2)
      .Bind_Property_Readonly(Geom_Hyperbola, Directrix1)
      .Bind_Property_Readonly(Geom_Hyperbola, Directrix2)
      .Bind_Property_Readonly(Geom_Hyperbola, Focal)
      .Bind_Property_Readonly(Geom_Hyperbola, Focus1)
      .Bind_Property_Readonly(Geom_Hyperbola, Focus2)
      .Bind_Property_Readonly(Geom_Hyperbola, OtherBranch)
      .Bind_Property_Readonly(Geom_Hyperbola, Parameter)
      .Bind_DownCast(Geom_Hyperbola)
      .End_Derive()

      .Begin_Derive(Geom_Parabola, Geom_Conic)
      .addConstructorFrom<Handle(Geom_Parabola), void(const gp_Parab &),
                          void(const gp_Ax2 &, const Standard_Real),
                          void(const gp_Ax1 &, const gp_Pnt &)>()
      .Bind_Property(Geom_Parabola, Parab, SetParab)
      .Bind_Property(Geom_Parabola, Focal, SetFocal)
      .Bind_Property_Readonly(Geom_Parabola, Directrix)
      .Bind_Property_Readonly(Geom_Parabola, Focus)
      .Bind_Property_Readonly(Geom_Parabola, Parameter)
      .Bind_DownCast(Geom_Parabola)
      .End_Derive()

      .Begin_Derive(Geom_Line, Geom_Curve)
      .addConstructorFrom<Handle(Geom_Line), void(const gp_Ax1 &),
                          void(const gp_Lin &),
                          void(const gp_Pnt &, const gp_Dir &)>()
      .Bind_Property(Geom_Line, Lin, SetLin)
      .Bind_Property(Geom_Line, Position, SetPosition)
      .Bind_Method(Geom_Line, SetDirection)
      .Bind_Method(Geom_Line, SetLocation)
      .Bind_DownCast(Geom_Line)
      .End_Derive()

      .Begin_Derive(Geom_OffsetCurve, Geom_Curve)
      .addConstructorFrom<Handle(Geom_OffsetCurve),
                          void(const Handle(Geom_Curve) &, const Standard_Real,
                               const gp_Dir &, const Standard_Boolean)>()
      .Bind_Method(Geom_OffsetCurve, SetBasisCurve)
      .Bind_Property_Readonly(Geom_OffsetCurve, BasisCurve)
      .Bind_Property(Geom_OffsetCurve, Direction, SetDirection)
      .Bind_Property(Geom_OffsetCurve, Offset, SetOffsetValue)
      .Bind_Method(Geom_OffsetCurve, GetBasisCurveContinuity)
      .Bind_DownCast(Geom_OffsetCurve)
      .End_Derive()

      .End_Namespace1();
}

static inline void luaocct_init_Geom_Point(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(Geom)

      .Begin_Derive(Geom_Point, Geom_Geometry)
      .addFunction(
          "Coord",
          +[](const Geom_Point &self) -> std::array<Standard_Real, 3> {
            std::array<Standard_Real, 3> result{};
            self.Coord(result[0], result[1], result[2]);
            return result;
          })
      .Bind_Method(Geom_Point, X)
      .Bind_Method(Geom_Point, Y)
      .Bind_Method(Geom_Point, Z)
      .Bind_Method(Geom_Point, Pnt)
      .Bind_Method(Geom_Point, Distance)
      .Bind_Method(Geom_Point, SquareDistance)
      .Bind_DownCast(Geom_Point)
      .End_Class()

      .Begin_Derive(Geom_CartesianPoint, Geom_Point)
      .addConstructorFrom<Handle(Geom_CartesianPoint), void(const gp_Pnt &),
                          void(const Standard_Real, const Standard_Real,
                               const Standard_Real)>()
      .Bind_Method(Geom_CartesianPoint, SetCoord)
      .Bind_Method(Geom_CartesianPoint, SetPnt)
      .Bind_Method(Geom_CartesianPoint, SetX)
      .Bind_Method(Geom_CartesianPoint, SetY)
      .Bind_Method(Geom_CartesianPoint, SetZ)
      .Bind_DownCast(Geom_CartesianPoint)
      .End_Class()

      .End_Namespace1();
}

static inline void luaocct_init_Geom_Surface(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(Geom)

      .Begin_Derive(Geom_Surface, Geom_Geometry)
      .Bind_Method(Geom_Surface, UReverse)
      .Bind_Method(Geom_Surface, UReversed)
      .Bind_Method(Geom_Surface, UReversedParameter)
      .Bind_Method(Geom_Surface, VReverse)
      .Bind_Method(Geom_Surface, VReversed)
      .Bind_Method(Geom_Surface, VReversedParameter)
      .addFunction(
          "TransformParameters",
          +[](const Geom_Surface &self)
              -> std::tuple<Standard_Real, Standard_Real, gp_Trsf> {
            Standard_Real u, v;
            gp_Trsf t{};
            self.TransformParameters(u, v, t);
            return {u, v, t};
          })
      .Bind_Method(Geom_Surface, ParametricTransformation)
      .addFunction(
          "Bounds",
          +[](const Geom_Surface &self) -> std::array<Standard_Real, 4> {
            std::array<Standard_Real, 4> result{};
            self.Bounds(result[0], result[1], result[2], result[3]);
            return result;
          })
      .Bind_Method(Geom_Surface, IsUClosed)
      .Bind_Method(Geom_Surface, IsVClosed)
      .Bind_Method(Geom_Surface, IsUPeriodic)
      .Bind_Method(Geom_Surface, UPeriod)
      .Bind_Method(Geom_Surface, IsVPeriodic)
      .Bind_Method(Geom_Surface, VPeriod)
      .Bind_Method(Geom_Surface, UIso)
      .Bind_Method(Geom_Surface, VIso)
      .Bind_Method(Geom_Surface, Continuity)
      .Bind_Method(Geom_Surface, IsCNu)
      .Bind_Method(Geom_Surface, IsCNv)
      .addFunction(
          "D0",
          +[](const Geom_Surface &self, const Standard_Real u,
              const Standard_Real v) -> gp_Pnt {
            gp_Pnt p{};
            self.D0(u, v, p);
            return p;
          })
      .addFunction(
          "D1",
          +[](const Geom_Surface &self, const Standard_Real u,
              const Standard_Real v) -> std::tuple<gp_Pnt, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec d1u{}, d1v{};
            self.D1(u, v, p, d1u, d1v);
            return {p, d1u, d1v};
          })
      .addFunction(
          "D2",
          +[](const Geom_Surface &self, const Standard_Real u,
              const Standard_Real v)
              -> std::tuple<gp_Pnt, gp_Vec, gp_Vec, gp_Vec, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec d1u{}, d1v{}, d2u{}, d2v{}, d2uv{};
            self.D2(u, v, p, d1u, d1v, d2u, d2v, d2uv);
            return {p, d1u, d1v, d2u, d2v, d2uv};
          })
      .addFunction(
          "D3",
          +[](const Geom_Surface &self, const Standard_Real u,
              const Standard_Real v)
              -> std::tuple<gp_Pnt, gp_Vec, gp_Vec, gp_Vec, gp_Vec, gp_Vec,
                            gp_Vec, gp_Vec, gp_Vec, gp_Vec> {
            gp_Pnt p{};
            gp_Vec d1u{}, d1v{}, d2u{}, d2v{}, d2uv{}, d3u{}, d3v{}, d3uuv{},
                d3uvv{};
            self.D3(u, v, p, d1u, d1v, d2u, d2v, d2uv, d3u, d3v, d3uuv, d3uvv);
            return {p, d1u, d1v, d2u, d2v, d2uv, d3u, d3v, d3uuv, d3uvv};
          })
      .Bind_Method(Geom_Surface, Value)
      .Bind_DownCast(Geom_Surface)
      .End_Class()

      .Begin_Derive(Geom_BoundedSurface, Geom_Surface)
      .Bind_DownCast(Geom_BoundedSurface)
      .End_Derive()

      .Begin_Derive(Geom_BSplineSurface, Geom_BoundedSurface)
      // .addConstructorFrom<Handle(Geom_BSplineSurface)>()
      .Bind_DownCast(Geom_BSplineSurface)
      .End_Derive()

      .Begin_Derive(Geom_BezierSurface, Geom_BoundedSurface)
      .Bind_DownCast(Geom_BezierSurface)
      .End_Derive()

      .Begin_Derive(Geom_RectangularTrimmedSurface, Geom_BoundedSurface)
      .Bind_DownCast(Geom_RectangularTrimmedSurface)
      .End_Derive()

      .Begin_Derive(Geom_ElementarySurface, Geom_Surface)
      .Bind_DownCast(Geom_ElementarySurface)
      .End_Derive()

      .Begin_Derive(Geom_ConicalSurface, Geom_ElementarySurface)
      .Bind_DownCast(Geom_ConicalSurface)
      .End_Derive()

      .Begin_Derive(Geom_CylindricalSurface, Geom_ElementarySurface)
      .Bind_DownCast(Geom_CylindricalSurface)
      .End_Derive()

      .Begin_Derive(Geom_Plane, Geom_ElementarySurface)
      .Bind_DownCast(Geom_Plane)
      .End_Derive()

      .Begin_Derive(Geom_SphericalSurface, Geom_ElementarySurface)
      .Bind_DownCast(Geom_SphericalSurface)
      .End_Derive()

      .Begin_Derive(Geom_ToroidalSurface, Geom_ElementarySurface)
      .Bind_DownCast(Geom_ToroidalSurface)
      .End_Derive()

      .Begin_Derive(Geom_OffsetSurface, Geom_Surface)
      .Bind_DownCast(Geom_OffsetSurface)
      .End_Derive()

      .Begin_Derive(Geom_SweptSurface, Geom_Surface)
      .Bind_DownCast(Geom_SweptSurface)
      .End_Derive()

      .Begin_Derive(Geom_SurfaceOfLinearExtrusion, Geom_SweptSurface)
      .Bind_DownCast(Geom_SurfaceOfLinearExtrusion)
      .End_Derive()

      .Begin_Derive(Geom_SurfaceOfRevolution, Geom_SweptSurface)
      .Bind_DownCast(Geom_SurfaceOfRevolution)
      .End_Derive()

      .End_Namespace1();
}

void luaocct_init_Geom(lua_State *L) {
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
      .Bind_DownCast(Geom_Geometry)
      .End_Derive()

      .End_Namespace1();

  luaocct_init_Geom_Curve(L);
  luaocct_init_Geom_Point(L);
  luaocct_init_Geom_Surface(L);
}
