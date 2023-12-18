#ifndef _LuaOCC_Header
#define _LuaOCC_Header

#include <lua.hpp>

#include <LuaBridge/LuaBridge.h>

#include <Geom_BSplineCurve.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <gp_XYZ.hxx>

#include <cstdint>

#ifdef _WIN32
#define LuaOCC_Export extern "C" __declspec(dllexport)
#else
#define LuaOCC_Export extern "C"
#endif

namespace luabridge {

template <class T> struct ContainerTraits;

template <class T> struct ContainerTraits<opencascade::handle<T>> {
  typedef T Type;

  static T *get(opencascade::handle<T> const &c) { return c.get(); }
};

} // namespace luabridge

LuaOCC_Export int32_t luaopen_luaocc(lua_State *L);

#undef LuaOCC_Export

#endif
