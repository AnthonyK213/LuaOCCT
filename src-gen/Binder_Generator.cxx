#include "Binder_Generator.hxx"

#include <algorithm>
#include <iterator>

Binder_Generator::Binder_Generator() : myIndex(nullptr), myTransUnit(nullptr) {}

Binder_Generator::~Binder_Generator() { Dispose(); }

bool Binder_Generator::Parse() {
  Dispose();

  myIndex = clang_createIndex(0, 0);

  std::string aHeader = myModDir + "/_" + myModName + ".h";

  std::vector<const char *> aClangArgs{};
  std::transform(
      myClangArgs.cbegin(), myClangArgs.cend(), std::back_inserter(aClangArgs),
      [](const std::string &theStr) -> const char * { return theStr.c_str(); });

  aClangArgs.push_back("-I");
  aClangArgs.push_back(myOcctIncDir.c_str());

  for (const std::string &aStr : myIncludeDirs) {
    aClangArgs.push_back("-I");
    aClangArgs.push_back(aStr.c_str());
  }

  myTransUnit = clang_parseTranslationUnit(
      myIndex, aHeader.c_str(), aClangArgs.data(), aClangArgs.size(), nullptr,
      0, CXTranslationUnit_DetailedPreprocessingRecord);

  if (myTransUnit == nullptr) {
    std::cout << "Unable to parse translation unit.\n";
    return false;
  }

  return true;
}

bool Binder_Generator::Generate(const std::string &theExportDir) {
  CXCursor aCursor = clang_getTranslationUnitCursor(myTransUnit);

  clang_visitChildren(
      aCursor,
      [](CXCursor theCursor, CXCursor theParent, CXClientData theClientData) {
        CXString aCursorInfoStr = clang_getCursorSpelling(theCursor);
        std::string aCursorInfo{clang_getCString(aCursorInfoStr)};

        Binder_Generator *aThis =
            static_cast<Binder_Generator *>(theClientData);

        if (aCursorInfo.rfind(aThis->ModName(), 0) == 0 &&
            clang_getCursorKind(theCursor) == CXCursor_ClassDecl) {
          std::cout << aCursorInfo << '\n';
        }

        clang_disposeString(aCursorInfoStr);

        return CXChildVisit_Continue;
      },
      this);

  std::string theExportFilePath = theExportDir + "/l" + myModName + ".h";
  std::cout << "Export module to: " << theExportFilePath << std::endl;

  return true;
}

int Binder_Generator::Save(const std::string &theFilePath) const {
  return clang_saveTranslationUnit(myTransUnit, theFilePath.c_str(),
                                   CXSaveTranslationUnit_None);
}

bool Binder_Generator::Load(const std::string &theFilePath) {
  CXIndex anIndex = clang_createIndex(0, 0);
  CXTranslationUnit anTransUnit =
      clang_createTranslationUnit(anIndex, theFilePath.c_str());

  if (anTransUnit == nullptr) {
    clang_disposeTranslationUnit(anTransUnit);
    clang_disposeIndex(anIndex);
    return false;
  }

  Dispose();
  myIndex = anIndex;
  myTransUnit = anTransUnit;

  return true;
}

void Binder_Generator::Dispose() {
  clang_disposeTranslationUnit(myTransUnit);
  clang_disposeIndex(myIndex);
}
