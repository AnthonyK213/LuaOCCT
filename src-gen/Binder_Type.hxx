#ifndef _LuaOCCT_Binder_Type_HeaderFile
#define _LuaOCCT_Binder_Type_HeaderFile

#include <clang-c/Index.h>

#include <string>

class Binder_Type {
public:
  Binder_Type(const CXType &theType);

  ~Binder_Type();

private:
  CXType myType;
};

#endif
