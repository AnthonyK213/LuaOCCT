#include "lGeomConvert.h"

void luaocct_init_GeomConvert(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(GeomConvert)

      .Begin_Class(GeomConvert)
      .addStaticFunction(
          "SplitBSplineCurve",
          luabridge::overload<const Handle(Geom_BSplineCurve) &,
                              const Standard_Integer, const Standard_Integer,
                              const Standard_Boolean>(
              &GeomConvert::SplitBSplineCurve),
          luabridge::overload<const Handle(Geom_BSplineCurve) &,
                              const Standard_Real, const Standard_Real,
                              const Standard_Real, const Standard_Boolean>(
              &GeomConvert::SplitBSplineCurve))
      .Bind_Method_Static(GeomConvert, CurveToBSplineCurve)
      .addStaticFunction(
          "ConcatG1",
          +[](const TColGeom_Array1OfBSplineCurve &arrayOfCurve,
              const TColStd_Array1OfReal &arrayOfToler,
              const Standard_Boolean closeFlag,
              const Standard_Real closedTolerance)
              -> std::tuple<TColGeom_Array1OfBSplineCurve, Standard_Boolean> {
            Standard_Boolean closedG1Flag = closeFlag;
            Handle(TColGeom_HArray1OfBSplineCurve) arrayOfConcatenated =
                nullptr;

            TColGeom_Array1OfBSplineCurve inputs(arrayOfCurve.First(), 0,
                                                 arrayOfCurve.Length() - 1);
            TColStd_Array1OfReal tolers(arrayOfToler.First(), 0,
                                        arrayOfToler.Length() - 1);

            try {
              GeomConvert::ConcatG1(inputs, tolers, arrayOfConcatenated,
                                    closedG1Flag, closedTolerance);
            } catch (const Standard_Failure &f) {
              throw std::runtime_error(f.GetMessageString());
            } catch (...) {
              throw std::runtime_error("Unkonw error");
            }

            TColGeom_Array1OfBSplineCurve result =
                arrayOfConcatenated->Array1();

            return {result, closedG1Flag};
          })
      .End_Class()

      .Begin_Class(GeomConvert_CompCurveToBSplineCurve)
      .addConstructor<void(), void(const Convert_ParameterisationType),
                      void(const Handle(Geom_BoundedCurve) &),
                      void(const Handle(Geom_BoundedCurve) &,
                           const Convert_ParameterisationType)>()
      .addFunction(
          "Add",
          luabridge::overload<const Handle(Geom_BoundedCurve) &,
                              const Standard_Real, const Standard_Boolean,
                              const Standard_Boolean, const Standard_Integer>(
              &GeomConvert_CompCurveToBSplineCurve::Add))
      .Bind_Property_Readonly(GeomConvert_CompCurveToBSplineCurve, BSplineCurve)
      .Bind_Method(GeomConvert_CompCurveToBSplineCurve, Clear)
      .End_Class()

      .End_Namespace1();
}
