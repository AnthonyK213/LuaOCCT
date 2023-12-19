#ifndef _LuaOCC_lStandard_Header
#define _LuaOCC_lStandard_Header

#include <Standard.hxx>
#include <Standard_Handle.hxx>

#include "bind.h"

namespace luabridge {

template <class T> struct ContainerTraits<opencascade::handle<T>> {
  using Type = T;

  static opencascade::handle<T> construct(T *c) { return c; }

  static T *get(const opencascade::handle<T> &c) { return c.get(); }
};

} // namespace luabridge

#endif
