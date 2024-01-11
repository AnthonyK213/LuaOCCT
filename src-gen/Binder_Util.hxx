#ifndef _LuaOCCT_Binder_Util_HeaderFile
#define _LuaOCCT_Binder_Util_HeaderFile

#include <clang-c/Index.h>

#include <string>

std::string Binder_Util_GetCString(const CXString &theStr);

std::string Binder_Util_GetCString(CXString &&theStr);

#endif
