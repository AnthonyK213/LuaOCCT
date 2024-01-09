#ifndef _LuaOCCT_Binder_Cursor_HeaderFile
#define _LuaOCCT_Binder_Cursor_HeaderFile

#include <clang-c/Index.h>

class Binder_Cursor {
public:
  explicit Binder_Cursor(const CXCursor &theCursor);

  ~Binder_Cursor();

private:
  CXCursor myCursor;
};

#endif
