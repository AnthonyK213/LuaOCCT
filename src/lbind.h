#ifndef _LuaOCCT_lbind_Header
#define _LuaOCCT_lbind_Header

// clang-format off
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Array.h>
#include <LuaBridge/Vector.h>
// clang-format on

#include "mod_header/_BRepBuilderAPI.h"
#include "mod_header/_BRepLib.h"
#include "mod_header/_Geom.h"
#include "mod_header/_GeomAbs.h"
#include "mod_header/_Poly.h"
#include "mod_header/_Standard.h"
#include "mod_header/_TopAbs.h"
#include "mod_header/_TopExp.h"
#include "mod_header/_TopoDS.h"
#include "mod_header/_gp.h"

#include <Geom2d_Curve.hxx>
#include <NCollection_Array1.hxx>
#include <NCollection_Array2.hxx>
#include <NCollection_List.hxx>
#include <OSD_FileSystem.hxx>
#include <TopLoc_Location.hxx>

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
    Standard_Integer i = 1;

    while (lua_next(L, abs_index) != 0) {
      auto item = Stack<T>::get(L, -1);

      if (!item) {
        lua_pop(L, lua_gettop(L) - init_stack_size);
        return item.error();
      }

      array1.SetValue(i, *item);

      lua_pop(L, 1);
      i++;
    }

    return array1;
  }
};

template <class T> struct Stack<NCollection_Array2<T>> {
  static Result push(lua_State *L, const NCollection_Array2<T> &array2) {
    const int init_stack_size = lua_gettop(L);

    lua_createtable(L, array2.NbRows(), 0);

    for (Standard_Integer i = 0; i < array2.NbRows(); ++i) {
      lua_pushinteger(L, static_cast<lua_Integer>(i + 1));

      NCollection_Array1<T> row{
          array2(i + array2.LowerRow(), array2.LowerCol()), 1,
          array2.RowLength()};

      auto result = Stack<NCollection_Array1<T>>::push(L, row);

      if (!result) {
        lua_pop(L, lua_gettop(L) - init_stack_size);
        return result;
      }

      lua_settable(L, -3);
    }

    return {};
  }

  static TypeResult<NCollection_Array2<T>> get(lua_State *L, int index) {
    if (!lua_istable(L, index)) {
      return makeErrorCode(ErrorCode::InvalidTypeCast);
    }

    const int init_stack_size = lua_gettop(L);

    const int nb_row = get_length(L, index);
    int row_length = 0;
    NCollection_Array2<T> array2{};

    const int abs_index = lua_absindex(L, index);

    lua_pushnil(L);
    Standard_Integer i = 1;
    Standard_Boolean is_first = Standard_True;

    while (lua_next(L, abs_index) != 0) {
      auto item = Stack<NCollection_Array1<T>>::get(L, -1);

      if (!item) {
        lua_pop(L, lua_gettop(L) - init_stack_size);
        return item.error();
      }

      if (is_first) {
        row_length = (*item).Length();
        array2 = NCollection_Array2<T>(1, nb_row, 1, row_length);
        is_first = Standard_False;
      } else {
        if (row_length != (*item).Length()) {
          lua_pop(L, lua_gettop(L) - init_stack_size);
          return makeErrorCode(ErrorCode::InvalidTypeCast);
        }
      }

      for (Standard_Integer j = 1; j <= row_length; ++j) {
        array2.SetValue(i, j, (*item)(j));
      }

      lua_pop(L, 1);
      i++;
    }

    return array2;
  }
};

} // namespace luabridge

#define LuaBridge__G(L) luabridge::getGlobalNamespace(L)

#define Begin_Namespace(N) beginNamespace(#N)
#define Begin_Namespace0() beginNamespace("LuaOCCT")
#define Begin_Namespace1(U) beginNamespace("LuaOCCT").beginNamespace(#U)
#define Begin_Namespace2(U, V)                                                 \
  beginNamespace("LuaOCCT").beginNamespace(#U).beginNamespace(#V)
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

#define Bind_DownCast(D)                                                       \
  addStaticFunction(                                                           \
      "DownCast", +[](const Handle(Standard_Transient) & h) -> Handle(D) {     \
        return Handle(D)::DownCast(h);                                         \
      })
#define Bind_DownCast1(D, B)                                                   \
  addStaticFunction(                                                           \
      "DownCast", +[](const Handle(B) & h) -> Handle(D) {                      \
        return Handle(D)::DownCast(h);                                         \
      })

#endif
