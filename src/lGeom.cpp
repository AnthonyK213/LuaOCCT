#include "lGeom.h"

int32_t luaocc_init_Geom(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace2(Geom, GeomAbs_Shape)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C0)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_G1)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C1)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_G2)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C2)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C3)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_CN)
      .End_Namespace2();

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
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(Geom)
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
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(Geom)
      .Begin_Derive(Geom_BoundedCurve, Geom_Curve)
      .Bind_Method(Geom_BoundedCurve, EndPoint)
      .Bind_Method(Geom_BoundedCurve, StartPoint)
      .End_Derive()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(Geom)
      .Begin_Derive(Geom_BSplineCurve, Geom_BoundedCurve)
      .Bind_Method(Geom_BSplineCurve, IncreaseDegree)
      .addFunction(
          "IncreaseMultiplicity",
          luabridge::overload<const Standard_Integer, const Standard_Integer>(
              &Geom_BSplineCurve::IncreaseMultiplicity),
          luabridge::overload<const Standard_Integer, const Standard_Integer,
                              const Standard_Integer>(
              &Geom_BSplineCurve::IncreaseMultiplicity))
      .Bind_Method(Geom_BSplineCurve, IncrementMultiplicity)
      .Bind_Method(Geom_BSplineCurve, IsG1)
      .Bind_Property_Readonly(Geom_BSplineCurve, Degree)
      .Bind_Property_Readonly(Geom_BSplineCurve, NbKnots)
      .Bind_Property_Readonly(Geom_BSplineCurve, NbPoles)
      .Bind_Method(Geom_BSplineCurve, IsEqual)
      .End_Derive()
      .End_Namespace1();

  LuaBridge__G(L)
      .Begin_Namespace1(Geom)
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

  return 0;
}
