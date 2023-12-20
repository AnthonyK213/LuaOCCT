#include "lGeom.h"

int32_t luaocc_init_Geom(lua_State *L) {
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
      .End_Class()
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
      .Bind_Method(Geom_Curve, D0)
      .Bind_Method(Geom_Curve, D1)
      .Bind_Method(Geom_Curve, D2)
      .Bind_Method(Geom_Curve, D3)
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
