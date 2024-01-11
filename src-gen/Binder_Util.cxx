#include "Binder_Util.hxx"

std::string Binder_Util_GetCString(const CXString &theStr) {
  return clang_getCString(theStr);
}

std::string Binder_Util_GetCString(CXString &&theStr) {
  std::string aStr = clang_getCString(theStr);
  clang_disposeString(theStr);
  return aStr;
}
