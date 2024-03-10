#include <luaocct/LOUtil_Curve.hxx>
#include <luaocct/LOUtil_Math.hxx>

#include <Extrema_ExtPC.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GeomConvert_CompCurveToBSplineCurve.hxx>
#include <GeomLProp_CLProps.hxx>
#include <GeomLib.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <ShapeUpgrade_SplitCurve3dContinuity.hxx>
#include <TColgp_HArray1OfPnt.hxx>

#include <limits>

Handle(Geom_Curve) LOUtil_Curve::Duplicate(const Handle(Geom_Curve) &
                                           theCurve) {
  return Handle(Geom_Curve)::DownCast(theCurve->Copy());
}

Standard_Boolean LOUtil_Curve::IsClosed(const Handle(Geom_Curve) & theCurve,
                                        const Standard_Real theTolerance) {
  return ShapeAnalysis_Curve::IsClosed(theCurve, theTolerance);
}

Standard_Real LOUtil_Curve::GetLength(const Handle(Geom_Curve) & theCurve,
                                      const Standard_Real t0,
                                      const Standard_Real t1) {
  GeomAdaptor_Curve aCrv(theCurve);
  return CPnts_AbscissaPoint::Length(aCrv, t0, t1);
}

Standard_Real LOUtil_Curve::GetLength(const Handle(Geom_Curve) & theCurve) {
  return GetLength(theCurve, theCurve->FirstParameter(),
                   theCurve->LastParameter());
}

Standard_Boolean LOUtil_Curve::LengthParameter(
    const Handle(Geom_Curve) & theCurve, const Standard_Real theSegmentLength,
    Standard_Real &theT, const Standard_Real theTolerance) {
  Standard_Real aLength = GetLength(theCurve);

  if (theSegmentLength > aLength || theSegmentLength < 0.0 ||
      aLength < gp::Resolution()) {
    return Standard_False;
  }

  GeomAdaptor_Curve aCurve(theCurve);
  CPnts_AbscissaPoint aPnt{aCurve, theSegmentLength, aCurve.FirstParameter(),
                           theTolerance};

  if (!aPnt.IsDone()) {
    return Standard_False;
  }

  theT = aPnt.Parameter();

  return Standard_True;
}

Standard_Boolean LOUtil_Curve::NormalizedLengthParameter(
    const Handle(Geom_Curve) & theCurve, const Standard_Real theS,
    Standard_Real &theT, const Standard_Real theTolerance) {
  Standard_Real aSegmentLength = GetLength(theCurve) * theS;
  return LengthParameter(theCurve, aSegmentLength, theT, theTolerance);
}

Standard_Boolean
LOUtil_Curve::PointAtNormalizedLength(const Handle(Geom_Curve) & theCurve,
                                      const Standard_Real theS, gp_Pnt &thePnt,
                                      const Standard_Real theTolerance) {
  Standard_Real t;

  if (!NormalizedLengthParameter(theCurve, theS, t, theTolerance))
    return Standard_False;

  thePnt = theCurve->Value(t);

  return Standard_True;
}

static Handle(Geom_Curve)
    extend(const Handle(Geom_Curve) & theCurve, LOAbs_CurveEnd theSide,
           const Standard_Real theLength, const Standard_Integer theCont) {
  if (theLength < gp::Resolution()) {
    return LOUtil_Curve::Duplicate(theCurve);
  }

  Standard_Real t = theSide == LOAbs_AtStart ? theCurve->FirstParameter()
                                           : theCurve->LastParameter();

  gp_Pnt pntEnd;
  gp_Vec dirEnd;
  theCurve->D1(t, pntEnd, dirEnd);
  dirEnd.Normalize();

  if (theSide == LOAbs_AtStart)
    dirEnd.Reverse();

  gp_Pnt target = pntEnd.XYZ() + dirEnd.XYZ() * theLength;
  auto aCurve = Handle(Geom_BoundedCurve)::DownCast(theCurve->Copy());

  if (aCurve.IsNull()) {
    return LOUtil_Curve::Duplicate(aCurve);
  } else {
    GeomLib::ExtendCurveToPoint(aCurve, target, 1, theSide == LOAbs_AtEnd);
    return aCurve;
  }
}

Handle(Geom_Curve) LOUtil_Curve::Extend(const Handle(Geom_Curve) & theCurve,
                                        LOAbs_CurveEnd theSide,
                                        const Standard_Real theLength,
                                        const Standard_Integer theCont) {
  if (IsClosed(theCurve)) {
    return Duplicate(theCurve);
  }

  switch (theSide) {
  case LOAbs_AtBoth: {
    Handle(Geom_Curve) aCrv = extend(theCurve, LOAbs_AtStart, theLength, theCont);
    return extend(aCrv, LOAbs_AtEnd, theLength, theCont);
  }

  default:
    return extend(theCurve, theSide, theLength, theCont);
  }
}

Handle(Geom_TrimmedCurve) LOUtil_Curve::Trim(const Handle(Geom_Curve) &
                                                 theCurve,
                                             const Standard_Real theT0,
                                             const Standard_Real theT1) {
  if (theT1 - theT0 <= Precision::Confusion() ||
      theT0 < theCurve->FirstParameter() || theT1 > theCurve->LastParameter()) {
    return nullptr;
  }

  return new Geom_TrimmedCurve(theCurve, theT0, theT1);
}

static Handle(Geom_TrimmedCurve)
    trimByLength(const Handle(Geom_Curve) & theCurve, LOAbs_CurveEnd theSide,
                 const Standard_Real theLength) {
  GeomAdaptor_Curve aCurve(theCurve);
  Standard_Real abscissa =
      theSide == LOAbs_AtStart ? theLength
                             : (LOUtil_Curve::GetLength(theCurve) - theLength);
  GCPnts_AbscissaPoint aPnt{aCurve, abscissa, aCurve.FirstParameter()};

  if (!aPnt.IsDone())
    return nullptr;

  Standard_Real t = aPnt.Parameter();

  if (theSide == LOAbs_AtStart) {
    return LOUtil_Curve::Trim(theCurve, t, theCurve->LastParameter());
  } else {
    return LOUtil_Curve::Trim(theCurve, theCurve->FirstParameter(), t);
  }
}

Handle(Geom_TrimmedCurve) LOUtil_Curve::TrimByLength(
    const Handle(Geom_Curve) & theCurve, LOAbs_CurveEnd theSide,
    const Standard_Real theLength) {
  switch (theSide) {
  case LOAbs_AtBoth: {
    auto aCrv = trimByLength(theCurve, LOAbs_AtStart, theLength);
    return trimByLength(aCrv, LOAbs_AtEnd, theLength);
  }

  default:
    return trimByLength(theCurve, theSide, theLength);
  }
}

Standard_Boolean LOUtil_Curve::IsLinear(const Handle(Geom_Curve) & theCurve,
                                        const Standard_Real theTolerance) {
  if (theCurve.IsNull()) {
    return false;
  }

  if (IsClosed(theCurve, theTolerance)) {
    return false;
  }

  Handle(Standard_Type) aType = theCurve->DynamicType();
  if (aType == STANDARD_TYPE(Geom_Line)) {
    return true;
  }
  if (aType == STANDARD_TYPE(Geom_Circle)) {
    return false;
  }

  Handle(TColgp_HArray1OfPnt) poles;
  Standard_Integer nbPoles = 0;

  if (aType == STANDARD_TYPE(Geom_BSplineCurve)) {
    Handle(Geom_BSplineCurve) bsc =
        Handle(Geom_BSplineCurve)::DownCast(theCurve);

    if (bsc->Degree() == 1) {
      return true;
    }

    nbPoles = bsc->NbPoles();
    poles = new TColgp_HArray1OfPnt(1, nbPoles);
    bsc->Poles(poles->ChangeArray1());
  }

  if (aType == STANDARD_TYPE(Geom_BezierCurve)) {
    Handle(Geom_BezierCurve) bzc = Handle(Geom_BezierCurve)::DownCast(theCurve);

    if (bzc->Degree() == 1) {
      return true;
    }

    nbPoles = bzc->NbPoles();
    poles = new TColgp_HArray1OfPnt(1, nbPoles);
    bzc->Poles(poles->ChangeArray1());
  }

  if (nbPoles < 2) {
    // https://github.com/Open-Cascade-SAS/OCCT/blob/master/src/GeomConvert/GeomConvert_CurveToAnaCurve.cxx#L197
    nbPoles = 23;
    Standard_Real t0 = theCurve->FirstParameter();
    Standard_Real t1 = theCurve->LastParameter();
    poles = new TColgp_HArray1OfPnt(1, nbPoles);
    Standard_Real dt = (t1 - t0) / (nbPoles - 1);
    poles->SetValue(1, theCurve->Value(t0));
    poles->SetValue(nbPoles, theCurve->Value(t1));

    for (Standard_Integer i = 2; i < nbPoles; ++i) {
      poles->SetValue(i, theCurve->Value(t0 + (i - 1) * dt));
    }
  }

  Standard_Real tol2 = theTolerance * theTolerance;
  gp_Vec aVec(poles->Value(1), poles->Value(nbPoles));
  gp_Lin aLin(poles->Value(1), gp_Dir(aVec));

  Standard_Real aMax = 0;
  for (Standard_Integer i = 1; i <= nbPoles; ++i) {
    Standard_Real dist = aLin.SquareDistance(poles->Value(i));
    if (dist > tol2) {
      return Standard_False;
    }
    if (dist > aMax) {
      aMax = dist;
    }
  }

  return Standard_True;
}

std::vector<Standard_Real>
LOUtil_Curve::ClosestParameters(const Handle(Geom_Curve) & theCurve,
                                const gp_Pnt &thePoint) {
  std::vector<Standard_Real> aResult{};

  Standard_Real t0 = theCurve->FirstParameter();
  Standard_Real t1 = theCurve->LastParameter();
  Standard_Real aSqrDist = std::numeric_limits<double>::infinity();

  GeomAdaptor_Curve anAdaptor(theCurve);
  Extrema_ExtPC anExtrema(thePoint, anAdaptor);

  if (anExtrema.IsDone()) {
    Standard_Integer nbExt = anExtrema.NbExt();
    Standard_Real aSqrtDistTemp;

    Standard_Real aParam;

    for (Standard_Integer i = 1; i <= nbExt; ++i) {
      aParam = anExtrema.Point(i).Parameter();

      if (aParam == t0 || aParam == t1)
        continue;

      if (anExtrema.IsMin(i)) {
        aSqrtDistTemp = anExtrema.SquareDistance(i);

        if (aSqrtDistTemp == aSqrDist) {
          aResult.push_back(aParam);
        } else if (aSqrtDistTemp < aSqrDist) {
          aSqrDist = aSqrtDistTemp;
          aResult.clear();
          aResult.push_back(aParam);
        }
      }
    }
  }

  // Check if the ends of the curve is the closest.

  Standard_Real aDist0 = thePoint.SquareDistance(theCurve->Value(t0));
  Standard_Real aDist1 = thePoint.SquareDistance(theCurve->Value(t1));

  if (aDist0 <= aSqrDist || aDist1 <= aSqrDist) {
    if (aDist0 < aDist1) {
      if (aDist0 < aSqrDist) {
        return {t0};
      } else {
        aResult.push_back(t0);
      }
    } else if (aDist0 > aDist1) {
      if (aDist1 < aSqrDist) {
        return {t1};
      } else {
        aResult.push_back(t1);
      }
    } else {
      if (aDist0 < aSqrDist) {
        return {t0, t1};
      } else {
        aResult.push_back(t0);
        aResult.push_back(t1);
      }
    }
  }

  return aResult;
}

TColStd_Array1OfReal
LOUtil_Curve::DivideByCount(const Handle(Geom_Curve) & theCurve,
                            const Standard_Integer &theNbSegments,
                            const Standard_Boolean theIncludeEnds) {
  TColStd_Array1OfReal aResult{};

  if (theNbSegments <= 0)
    return aResult;

  Standard_Integer nbPnt = theNbSegments + 1;
  GeomAdaptor_Curve aCurve(theCurve);
  GCPnts_UniformAbscissa aPoints(aCurve, nbPnt);

  if (!aPoints.IsDone()) {
    return aResult;
  }

  Standard_Integer s, e;

  if (theIncludeEnds) {
    aResult.Resize(1, nbPnt, Standard_False);
    s = 1;
    e = nbPnt;
  } else {
    if (nbPnt <= 2) {
      return aResult;
    }

    aResult.Resize(1, nbPnt - 2, Standard_False);
    s = 2;
    e = nbPnt - 1;
  }

  for (int i = s, j = 1; i <= e; ++i, ++j) {
    aResult.SetValue(i, aPoints.Parameter(i));
  }

  return aResult;
}

static inline Standard_Boolean
isG2(const gp_Pnt &thisStart, const gp_Dir &thisTangentStart,
     double thisCurvatureStart, const gp_Pnt &prevEnd,
     const gp_Dir &prevTangentEnd, double prevCurvatureEnd) {
  return thisStart.Distance(prevEnd) < Precision::Confusion() &&
         thisTangentStart.IsParallel(prevTangentEnd, Precision::Confusion()) &&
         LOUtil_Math::EpsilonEquals(thisCurvatureStart, prevCurvatureEnd,
                                    Precision::Confusion());
}

std::vector<Handle(Geom_BoundedCurve)>
LOUtil_Curve::Explode(const Handle(Geom_Curve) & theCurve) {
  std::vector<Handle(Geom_BoundedCurve)> aResult{};

  ShapeUpgrade_SplitCurve3dContinuity aSplitter{};
  aSplitter.Init(theCurve);
  aSplitter.SetCriterion(GeomAbs_C1);
  aSplitter.Perform(Standard_True);
  const Handle(TColGeom_HArray1OfCurve) &theCurves = aSplitter.GetCurves();

  if (theCurves.IsNull()) {
    return aResult;
  }

  aResult.reserve(theCurves->Size());

  // Connection buffer.
  GeomConvert_CompCurveToBSplineCurve aBuffer{};

  GeomLProp_CLProps aProps(2, gp::Resolution());
  gp_Pnt prevEnd, thisStart, thisEnd = gp::Origin();
  gp_Dir prevTangentEnd, thisTangentStart, thisTangentEnd = gp::DZ();
  double prevCurvatureEnd, thisCurvatureStart, thisCurvatureEnd = -1.0;

  for (const Handle(Geom_Curve) & aCurve : *theCurves) {
    auto aBndCrv = Handle(Geom_BoundedCurve)::DownCast(aCurve);

    if (aBndCrv.IsNull())
      continue;

    aProps.SetCurve(aBndCrv);

    // Start point of the current curve.
    aProps.SetParameter(aBndCrv->FirstParameter());
    thisStart = aProps.Value();
    aProps.Tangent(thisTangentStart);
    thisCurvatureStart = aProps.Curvature();

    // End point of the previous curve.
    prevEnd = thisEnd;
    prevTangentEnd = thisTangentEnd;
    prevCurvatureEnd = thisCurvatureEnd;

    // End point of the current curve.
    aProps.SetParameter(aBndCrv->LastParameter());
    thisEnd = aProps.Value();
    aProps.Tangent(thisTangentEnd);
    thisCurvatureEnd = aProps.Curvature();

    if (aBuffer.BSplineCurve().IsNull()) {
      // If aBuffer is empty, pushing current curve to aBuffer is the only
      // choice. :P
      aBuffer.Add(aBndCrv, Precision::Confusion(), Standard_True);
      continue;
    } else if (isG2(thisStart, thisTangentStart, thisCurvatureStart, prevEnd,
                    prevTangentEnd, prevCurvatureEnd)) {
      // If G2, try connect current curve to the buffer.
      // If success, jump to the next loop directly.
      if (aBuffer.Add(aBndCrv, Precision::Confusion(), Standard_True))
        continue;
    }

    // If not G2, which means theCurve needs to "explode" here, so just submit
    // aBuffer to aResult, clear aBuffer, push current curve to aBuffer, build
    // another curve in the next loop.
    aResult.push_back(aBuffer.BSplineCurve());
    aBuffer.Clear();
    aBuffer.Add(aBndCrv, Precision::Confusion(), Standard_True);
  }

  // Check if the first and the last curve are able to connect.
  if (!aResult.empty()) {
    Handle(Geom_BoundedCurve) firstCurve = aResult[0];

    // Start point of the first curve.
    aProps.SetCurve(firstCurve);
    aProps.SetParameter(firstCurve->FirstParameter());
    thisStart = aProps.Value();
    aProps.Tangent(thisTangentStart);
    thisCurvatureStart = aProps.Curvature();

    if (isG2(thisStart, thisTangentStart, thisCurvatureStart, thisEnd,
             thisTangentEnd, thisCurvatureEnd)) {
      if (aBuffer.Add(firstCurve, Precision::Confusion(), Standard_True)) {
        // If succeed to connect, replace the first curve with the connected
        // curve.
        aResult[0] = aBuffer.BSplineCurve();
        return aResult;
      }
    }
  }

  // If the last curve cannot connect to the first curve, push it to aResult.
  Handle(Geom_BoundedCurve) lastCurve = aBuffer.BSplineCurve();
  if (!lastCurve.IsNull())
    aResult.push_back(lastCurve);

  return aResult;
}
