#ifndef _LuaOCCT_Binder_Util_HeaderFile
#define _LuaOCCT_Binder_Util_HeaderFile

#include <clang-c/Index.h>

#include <sstream>
#include <string>

std::string Binder_Util_GetCString(const CXString &theStr);

std::string Binder_Util_GetCString(CXString &&theStr);

template <typename Iter_, typename Fn_>
std::string Binder_Util_Join(Iter_ theFirst, Iter_ theLast, Fn_ theFn,
                             const std::string &theSep = ", ");

#include "detail/Binder_Util.inl"

#endif
