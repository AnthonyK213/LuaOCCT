#ifndef _LuaOCCT_LOUtil_Curve_HeaderFile
#define _LuaOCCT_LOUtil_Curve_HeaderFile

#include <GCPnts_AbscissaPoint.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <TColGeom_Array1OfCurve.hxx>

#include "LOAbs_CurveEnd.hxx"
#include <vector>

class LOUtil_Curve {
public:
  Standard_EXPORT static Handle(Geom_Curve)
      Duplicate(const Handle(Geom_Curve) & theCurve);

  Standard_EXPORT static Standard_Boolean
  IsClosed(const Handle(Geom_Curve) & theCurve,
           const Standard_Real theTolerance = Precision::Confusion());

  Standard_EXPORT static Standard_Real
  GetLength(const Handle(Geom_Curve) & theCurve, const Standard_Real t0,
            const Standard_Real t1);

  Standard_EXPORT static Standard_Real GetLength(const Handle(Geom_Curve) &
                                                 theCurve);

  Standard_EXPORT static Standard_Boolean
  LengthParameter(const Handle(Geom_Curve) & theCurve,
                  const Standard_Real theSegmentLength, Standard_Real &theT,
                  const Standard_Real theTolerance = Precision::Confusion());

  Standard_EXPORT static Standard_Boolean NormalizedLengthParameter(
      const Handle(Geom_Curve) & theCurve, const Standard_Real theS,
      Standard_Real &theT,
      const Standard_Real theTolerance = Precision::Confusion());

  Standard_EXPORT static Standard_Boolean PointAtNormalizedLength(
      const Handle(Geom_Curve) & theCurve, const Standard_Real theS,
      gp_Pnt &thePnt,
      const Standard_Real theTolerance = Precision::Confusion());

  Standard_EXPORT static Handle(Geom_Curve)
      Extend(const Handle(Geom_Curve) & theCurve, LOAbs_CurveEnd theSide,
             const Standard_Real theLength, const Standard_Integer theCont);

  Standard_EXPORT static Handle(Geom_TrimmedCurve)
      Trim(const Handle(Geom_Curve) & theCurve, const Standard_Real theT0,
           const Standard_Real theT1);

  Standard_EXPORT static Handle(Geom_TrimmedCurve)
      TrimByLength(const Handle(Geom_Curve) & theCurve, LOAbs_CurveEnd theSide,
                   const Standard_Real theLength);

  Standard_EXPORT static Standard_Boolean
  IsLinear(const Handle(Geom_Curve) & theCurve,
           const Standard_Real theTolerance = Precision::Confusion());

  Standard_EXPORT static std::vector<Standard_Real>
  ClosestParameters(const Handle(Geom_Curve) & theCurve,
                    const gp_Pnt &thePoint);

  Standard_EXPORT static TColStd_Array1OfReal
  DivideByCount(const Handle(Geom_Curve) & theCurve,
                const Standard_Integer &theNbSegments,
                const Standard_Boolean theIncludeEnds);

  Standard_EXPORT static std::vector<Handle(Geom_BoundedCurve)>
  Explode(const Handle(Geom_Curve) & theCurve);
};

#endif
