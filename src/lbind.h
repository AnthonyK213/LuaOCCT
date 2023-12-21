#ifndef _LuaOCC_lbind_Header
#define _LuaOCC_lbind_Header

#include <lua.hpp>

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

#include <Geom2d_Curve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <NCollection_Array1.hxx>
#include <NCollection_List.hxx>
#include <Poly_Triangle.hxx>
#include <Poly_Triangulation.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <TopLoc_Location.hxx>
#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax22d.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Cone.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Elips.hxx>
#include <gp_Elips2d.hxx>
#include <gp_GTrsf.hxx>
#include <gp_GTrsf2d.hxx>
#include <gp_Hypr.hxx>
#include <gp_Hypr2d.hxx>
#include <gp_Lin.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Mat.hxx>
#include <gp_Mat2d.hxx>
#include <gp_Parab.hxx>
#include <gp_Parab2d.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Quaternion.hxx>
#include <gp_QuaternionNLerp.hxx>
#include <gp_QuaternionSLerp.hxx>
#include <gp_Sphere.hxx>
#include <gp_Torus.hxx>
#include <gp_Trsf.hxx>
#include <gp_Trsf2d.hxx>
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx>
#include <gp_XY.hxx>
#include <gp_XYZ.hxx>

#include <tuple>
#include <vector>

namespace luabridge {

template <class T> struct ContainerTraits<opencascade::handle<T>> {
  using Type = T;

  static opencascade::handle<T> construct(T *c) { return c; }

  static T *get(const opencascade::handle<T> &c) { return c.get(); }
};

template <class T> struct Stack<NCollection_Array1<T>> {
  static Result push(lua_State *L, const NCollection_Array1<T> &array1) {
    const int init_stack_size = lua_gettop(L);

    lua_createtable(L, array1.Size(), 0);

    for (Standard_Integer i = 0; i < array1.Size(); ++i) {
      lua_pushinteger(L, static_cast<lua_Integer>(i + 1));

      auto result = Stack<T>::push(L, array1.Value(i + array1.Lower()));

      if (!result) {
        lua_pop(L, lua_gettop(L) - init_stack_size);
        return result;
      }

      lua_settable(L, -3);
    }

    return {};
  }

  static TypeResult<NCollection_Array1<T>> get(lua_State *L, int index) {
    if (!lua_istable(L, index)) {
      return makeErrorCode(ErrorCode::InvalidTypeCast);
    }

    const int init_stack_size = lua_gettop(L);

    NCollection_Array1<T> array1{1, get_length(L, index)};

    const int abs_index = lua_absindex(L, index);

    lua_pushnil(L);

    while (lua_next(L, abs_index) != 0) {
      auto item = Stack<T>::get(L, -1);

      if (!item) {
        lua_pop(L, lua_gettop(L) - init_stack_size);
        return item.error();
      }

      array1.SetValue(abs_index, *item);

      lua_pop(L, 1);
    }

    return array1;
  }
};

} // namespace luabridge

#define LuaBridge__G(L) luabridge::getGlobalNamespace(L)

#define Begin_Namespace(N) beginNamespace(#N)
#define Begin_Namespace0() beginNamespace("LuaOCC")
#define Begin_Namespace1(U) beginNamespace("LuaOCC").beginNamespace(#U)
#define Begin_Namespace2(U, V)                                                 \
  beginNamespace("LuaOCC").beginNamespace(#U).beginNamespace(#V)
#define End_Namespace() endNamespace()
#define End_Namespace0() endNamespace()
#define End_Namespace1() endNamespace().endNamespace()
#define End_Namespace2() endNamespace().endNamespace().endNamespace()

#define Begin_Class(T) beginClass<T>(#T)
#define End_Class() endClass()

#define Begin_Derive(D, B) deriveClass<D, B>(#D)
#define End_Derive() End_Class()

#define Bind_Enum(E, V) addVariable(#V, E::V)

#define Bind_Property(T, G, S)                                                 \
  addProperty(#G "_", &T::G, &T::S)                                            \
      .addFunction(#G, &T::G)                                                  \
      .addFunction(#S, &T::S)
#define Bind_Property_Readonly(T, G)                                           \
  addProperty(#G "_", &T::G).addFunction(#G, &T::G)

#define Bind_Method(T, M) addFunction(#M, &T::M)
#define Bind_Method_Static(T, M) addStaticFunction(#M, &T::M)

#endif
