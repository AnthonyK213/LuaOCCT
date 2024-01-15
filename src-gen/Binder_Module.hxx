#ifndef _LuaOCCT_Binder_Module_HeaderFile
#define _LuaOCCT_Binder_Module_HeaderFile

#include <string>
#include <vector>

#include "Binder_Cursor.hxx"

class Binder_Generator;

class Binder_Module {
  friend class Binder_Generator;

public:
  Binder_Module(const std::string &theName, const Binder_Generator &theParent);

  ~Binder_Module();

protected:
  bool parse();

  bool generate(const std::string &theExportDir = ".");

  int save(const std::string &theFilePath) const;

  bool load(const std::string &theFilePath);

  void dispose();

private:
  std::string myName;
  const Binder_Generator *myParent;

  CXIndex myIndex;
  CXTranslationUnit myTransUnit;
};

#endif
