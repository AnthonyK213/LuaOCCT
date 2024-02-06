#ifndef _LuaOCCT_util_curve_HeaderFile
#define _LuaOCCT_util_curve_HeaderFile

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

#include <vector>

namespace luaocct {
namespace util {
namespace Curve {

enum class CurveEnd : Standard_Integer { None = 0, Start, End, Both };

Standard_EXPORT Handle(Geom_Curve)
    Duplicate(const Handle(Geom_Curve) & theCurve);

Standard_EXPORT Standard_Boolean
IsClosed(const Handle(Geom_Curve) & theCurve,
         const Standard_Real theTolerance = Precision::Confusion());

Standard_EXPORT Standard_Real GetLength(const Handle(Geom_Curve) & theCurve,
                                        const Standard_Real t0,
                                        const Standard_Real t1);

Standard_EXPORT Standard_Real GetLength(const Handle(Geom_Curve) & theCurve);

Standard_EXPORT Standard_Boolean
LengthParameter(const Handle(Geom_Curve) & theCurve,
                const Standard_Real theSegmentLength, Standard_Real &theT,
                const Standard_Real theTolerance = Precision::Confusion());

Standard_EXPORT Standard_Boolean NormalizedLengthParameter(
    const Handle(Geom_Curve) & theCurve, const Standard_Real theS,
    Standard_Real &theT,
    const Standard_Real theTolerance = Precision::Confusion());

Standard_EXPORT Standard_Boolean PointAtNormalizedLength(
    const Handle(Geom_Curve) & theCurve, const Standard_Real theS,
    gp_Pnt &thePnt, const Standard_Real theTolerance = Precision::Confusion());

Standard_EXPORT Handle(Geom_Curve)
    Extend(const Handle(Geom_Curve) & theCurve, CurveEnd theSide,
           const Standard_Real theLength, const Standard_Integer theCont);

Standard_EXPORT Handle(Geom_TrimmedCurve)
    Trim(const Handle(Geom_Curve) & theCurve, const Standard_Real theT0,
         const Standard_Real theT1);

Standard_EXPORT Handle(Geom_TrimmedCurve)
    TrimByLength(const Handle(Geom_Curve) & theCurve, CurveEnd theSide,
                 const Standard_Real theLength);

Standard_EXPORT Standard_Boolean
IsLinear(const Handle(Geom_Curve) & theCurve,
         const Standard_Real theTolerance = Precision::Confusion());

Standard_EXPORT std::vector<Standard_Real>
ClosestParameters(const Handle(Geom_Curve) & theCurve, const gp_Pnt &thePoint);

Standard_EXPORT TColStd_Array1OfReal DivideByCount(
    const Handle(Geom_Curve) & theCurve, const Standard_Integer &theNbSegments,
    const Standard_Boolean theIncludeEnds);

Standard_EXPORT std::vector<Handle(Geom_BoundedCurve)>
Explode(const Handle(Geom_Curve) & theCurve);

} // namespace Curve
} // namespace util
} // namespace luaocct

#endif
