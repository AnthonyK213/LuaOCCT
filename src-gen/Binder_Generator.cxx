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
  Binder_Cursor aCursor = clang_getTranslationUnitCursor(myTransUnit);

  std::vector<Binder_Cursor> aClasses =
      aCursor.GetChildrenOfKind(CXCursor_ClassDecl);

  std::cout << ".beginNameSpace(\"LuaOCCT\")\n";
  std::cout << ".beginNameSpace(\"" << ModName() << "\")\n\n";

  for (const auto &aClass : aClasses) {
    std::string aClassSpelling = aClass.Spelling();

    if (aClassSpelling.rfind(ModName()) != 0 || aClass.GetChildren().empty())
      continue;

    std::cout << "-- Binding class: " << aClassSpelling << '\n';

    auto aBases = aClass.Bases();

    if (aBases.empty()) {
      std::cout << ".beginClass<" << aClassSpelling << ">(\"" << aClassSpelling
                << "\")\n";
    } else {
      std::cout << ".deriveClass<" << aClassSpelling << ", "
                << aBases[0].GetDefinition().Spelling() << ">(\""
                << aClassSpelling << "\")\n";
    }

    // Binding ctor.
    if (aClass.IsTransient()) {
      std::cout << ".addConstructorFrom<opencascade::handle<" << aClassSpelling
                << ">"
                << ">()\n";
    } else {
      std::cout << ".addConstructor<"
                << ">()\n";
    }

    // Binding methods.

    // Binding properties.

    std::cout << ".endClass()\n";

    std::cout << '\n';
  }

  std::cout << ".endNameSpace()\n";
  std::cout << ".endNameSpace();\n";

  std::string theExportFilePath = theExportDir + "/l" + myModName + ".h";
  std::cout << "\nExport module to: " << theExportFilePath << std::endl;

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
