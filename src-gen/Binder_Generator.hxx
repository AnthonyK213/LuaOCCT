#ifndef _LuaOCCT_Binder_Generator_HeaderFile
#define _LuaOCCT_Binder_Generator_HeaderFile

#include <clang-c/Index.h>

#include "Binder_Cursor.hxx"
#include "Binder_Module.hxx"

#include <iostream>
#include <set>
#include <string>
#include <vector>

class Binder_Generator {
public:
  Binder_Generator();

  ~Binder_Generator();

  const std::string &ModDir() const { return myModDir; }

  Binder_Generator &SetModDir(const std::string &theModDir) {
    myModDir = theModDir;
    return *this;
  }

  const std::string &OcctIncDir() const { return myOcctIncDir; }

  Binder_Generator &SetOcctIncDir(const std::string &theOcctIncDir) {
    myOcctIncDir = theOcctIncDir;
    return *this;
  }

  const std::string &ExportDir() const { return myExportDir; }

  Binder_Generator &SetExportDir(const std::string &theExportDir) {
    myExportDir = theExportDir;
    return *this;
  }

  const std::vector<std::string> &IncludeDirs() const { return myIncludeDirs; }

  Binder_Generator &
  SetIncludeDirs(const std::vector<std::string> &theIncludeDirs) {
    myIncludeDirs = theIncludeDirs;
    return *this;
  }

  const std::vector<std::string> &ClangArgs() const { return myClangArgs; }

  Binder_Generator &SetClangArgs(const std::vector<std::string> &theClangArgs) {
    myClangArgs = theClangArgs;
    return *this;
  }

  const std::shared_ptr<Binder_Module> &Module() const { return myCurMod; }

  void SetModule(const std::shared_ptr<Binder_Module> &theModule) {
    myCurMod = theModule;
  }

  bool AddVisitedClass(const std::string &theClass);

  bool Parse();

  bool Generate(const std::string &theExportDir = ".");

  int Save(const std::string &theFilePath) const;

  bool Load(const std::string &theFilePath);

private:
  std::string myModDir{};
  std::string myOcctIncDir{};
  std::string myExportDir{};
  std::vector<std::string> myIncludeDirs{};
  std::vector<std::string> myClangArgs{};

  std::shared_ptr<Binder_Module> myCurMod;

  std::set<std::string> myVisitedClasses{};
};

#endif
