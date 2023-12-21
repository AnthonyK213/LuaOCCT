#include "lGeomAbs.h"

void luaocc_init_GeomAbs(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(GeomAbs)

      .Begin_Namespace(GeomAbs_BSplKnotDistribution)
      .Bind_Enum(GeomAbs_BSplKnotDistribution, GeomAbs_NonUniform)
      .Bind_Enum(GeomAbs_BSplKnotDistribution, GeomAbs_Uniform)
      .Bind_Enum(GeomAbs_BSplKnotDistribution, GeomAbs_QuasiUniform)
      .Bind_Enum(GeomAbs_BSplKnotDistribution, GeomAbs_PiecewiseBezier)
      .End_Namespace()

      .Begin_Namespace(GeomAbs_CurveType)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_Line)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_Circle)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_Ellipse)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_Hyperbola)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_Parabola)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_BezierCurve)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_BSplineCurve)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_OffsetCurve)
      .Bind_Enum(GeomAbs_CurveType, GeomAbs_OtherCurve)
      .End_Namespace()

      .Begin_Namespace(GeomAbs_IsoType)
      .Bind_Enum(GeomAbs_IsoType, GeomAbs_IsoU)
      .Bind_Enum(GeomAbs_IsoType, GeomAbs_IsoV)
      .Bind_Enum(GeomAbs_IsoType, GeomAbs_NoneIso)
      .End_Namespace()

      .Begin_Namespace(GeomAbs_JoinType)
      .Bind_Enum(GeomAbs_JoinType, GeomAbs_Arc)
      .Bind_Enum(GeomAbs_JoinType, GeomAbs_Tangent)
      .Bind_Enum(GeomAbs_JoinType, GeomAbs_Intersection)
      .End_Namespace()

      .Begin_Namespace(GeomAbs_Shape)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C0)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_G1)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C1)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_G2)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C2)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_C3)
      .Bind_Enum(GeomAbs_Shape, GeomAbs_CN)
      .End_Namespace()

      .Begin_Namespace(GeomAbs_SurfaceType)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_Plane)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_Cylinder)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_Cone)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_Sphere)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_Torus)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_BezierSurface)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_BSplineSurface)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_SurfaceOfRevolution)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_SurfaceOfExtrusion)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_OffsetSurface)
      .Bind_Enum(GeomAbs_SurfaceType, GeomAbs_OtherSurface)
      .End_Namespace()

      .End_Namespace1();
}
