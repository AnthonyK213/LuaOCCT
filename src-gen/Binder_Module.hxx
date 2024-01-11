#ifndef _LuaOCCT_Binder_Module_HeaderFile
#define _LuaOCCT_Binder_Module_HeaderFile

#include <string>
#include <vector>

#include "Binder_Cursor.hxx"

class Binder_Module {
public:
  explicit Binder_Module(const std::string &theName);

  ~Binder_Module();

private:
  std::string myName;
};

#endif
