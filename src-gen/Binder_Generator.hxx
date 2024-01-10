#ifndef _LuaOCCT_Binder_Generator_HeaderFile
#define _LuaOCCT_Binder_Generator_HeaderFile

#include <clang-c/Index.h>

#include <iostream>
#include <string>
#include <vector>

class Binder_Generator {
public:
  Binder_Generator();

  ~Binder_Generator();

  Binder_Generator &SetModName(const std::string &theModName) {
    myModName = theModName;
    return *this;
  }

  Binder_Generator &SetModDir(const std::string &theModDir) {
    myModDir = theModDir;
    return *this;
  }

  Binder_Generator &SetOcctIncDir(const std::string &theOcctIncDir) {
    myOcctIncDir = theOcctIncDir;
    return *this;
  }

  Binder_Generator &
  SetIncludeDirs(const std::vector<std::string> &theIncludeDirs) {
    myIncludeDirs = theIncludeDirs;
    return *this;
  }

  Binder_Generator &SetClangArgs(const std::vector<std::string> &theClangArgs) {
    myClangArgs = theClangArgs;
    return *this;
  }

  const std::string &ModName() const { return myModName; }

  bool Parse();

  bool Generate(const std::string &theExportDir = ".");

  int Save(const std::string &theFilePath) const;

  bool Load(const std::string &theFilePath);

private:
  void Dispose();

private:
  std::string myModName{};
  std::string myModDir{};
  std::string myOcctIncDir{};
  std::vector<std::string> myIncludeDirs{};
  std::vector<std::string> myClangArgs{};

  CXIndex myIndex;
  CXTranslationUnit myTransUnit;
};

#endif
