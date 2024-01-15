#include "Binder_Module.hxx"
#include "Binder_Generator.hxx"

#include <algorithm>
#include <iterator>

Binder_Module::Binder_Module(const std::string &theName,
                             const Binder_Generator &theParent)
    : myName(theName), myParent(&theParent), myIndex(nullptr),
      myTransUnit(nullptr) {}

Binder_Module::~Binder_Module() {}

bool Binder_Module::parse() {
  dispose();

  myIndex = clang_createIndex(0, 0);

  std::string aHeader = myParent->ModDir() + "/_" + myName + ".h";

  std::vector<const char *> aClangArgs{};
  std::transform(
      myParent->ClangArgs().cbegin(), myParent->ClangArgs().cend(),
      std::back_inserter(aClangArgs),
      [](const std::string &theStr) -> const char * { return theStr.c_str(); });

  aClangArgs.push_back("-I");
  aClangArgs.push_back(myParent->OcctIncDir().c_str());

  for (const std::string &aStr : myParent->IncludeDirs()) {
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

struct ClassAttachment {
  std::string mySpelling;
  std::ostream &myStream;
};

static bool generateCtor(const Binder_Cursor &theClass,
                         std::ostream &theStream) {
  std::string aClassSpelling = theClass.Spelling();
  int anIndex = 0;

  if (theClass.IsTransient()) {
    theStream << ".addConstructorFrom<opencascade::handle<" << aClassSpelling
              << ">";
    anIndex++;
  } else {
    theStream << ".addConstructor<";
  }

  if (theClass.NeedsDefaultCtor()) {
    if (anIndex > 0) {
      theStream << ", ";
    }

    theStream << "void()";
    anIndex++;
  }

  std::vector<Binder_Cursor> aCtors =
      theClass.GetChildrenOfKind(CXCursor_Constructor, true);

  for (const auto &aCtor : aCtors) {
    if (anIndex > 0) {
      theStream << ", ";
    }

    theStream << "void(";

    std::vector<Binder_Cursor> aParams = aCtor.Parameters();

    int anIdx = 0;
    for (const auto &aParam : aParams) {
      if (anIdx > 0)
        theStream << ", ";

      theStream << aParam.Type().Spelling();
      anIdx++;
    }

    theStream << ")";
    anIndex++;
  }

  theStream << ">()\n";

  return true;
}

static bool isIgnoredMethod(const Binder_Cursor &theMethod) {
  if (theMethod.IsOverride())
    return true;

  std::string aFuncSpelling = theMethod.Spelling();

  if (aFuncSpelling == "DumpJson" || aFuncSpelling == "get_type_name" ||
      aFuncSpelling == "get_type_descriptor") {
    return true;
  }

  // TODO: Operator overload

  return false;
}

static bool generateMethods(const Binder_Cursor &theClass,
                            std::ostream &theStream) {
  std::string aClassSpelling = theClass.Spelling();
  std::vector<Binder_Cursor> aMethods =
      theClass.GetChildrenOfKind(CXCursor_CXXMethod, true);

  for (const auto &aMethod : aMethods) {
    std::string aFuncSpelling = aMethod.Spelling();

    if (isIgnoredMethod(aMethod))
      continue;

    theStream << ".addFunction(\"" << aFuncSpelling << "\", &" << aClassSpelling
              << "::" << aFuncSpelling << ")\n";
  }

  if (theClass.IsTransient()) {
    theStream << ".addStaticFunction(\"DownCast\", +[](const "
                 "Handle(Standard_Transient) &h) { return Handle("
              << aClassSpelling << ")::DownCast(h); })\n";
  }

  return true;
}

static bool generateClass(const Binder_Cursor &theClass,
                          std::ostream &theStream) {
  std::string aClassSpelling = theClass.Spelling();
  theStream << "-- Class: " << aClassSpelling << '\n';
  std::vector<Binder_Cursor> aBases = theClass.Bases();

  if (aBases.empty()) {
    theStream << ".beginClass<" << aClassSpelling << ">(\"" << aClassSpelling
              << "\")\n";
  } else {
    theStream << ".deriveClass<" << aClassSpelling << ", "
              << aBases[0].GetDefinition().Spelling() << ">(\""
              << aClassSpelling << "\")\n";
  }

  generateCtor(theClass, theStream);
  generateMethods(theClass, theStream);

  theStream << ".endClass()\n\n";

  return true;
}

bool Binder_Module::generate(const std::string &theExportDir) {
  Binder_Cursor aCursor = clang_getTranslationUnitCursor(myTransUnit);
  std::ostream &aStream = std::cout;

  std::vector<Binder_Cursor> aClasses =
      aCursor.GetChildrenOfKind(CXCursor_ClassDecl);

  aStream << ".beginNameSpace(\"LuaOCCT\")\n";
  aStream << ".beginNameSpace(\"" << myName << "\")\n\n";

  for (const auto &aClass : aClasses) {
    std::string aClassSpelling = aClass.Spelling();

    if (aClassSpelling.rfind(myName, 0) != 0 || aClass.GetChildren().empty())
      continue;

    generateClass(aClass, std::cout);
  }

  aStream << ".endNameSpace()\n";
  aStream << ".endNameSpace();\n";

  std::string theExportFilePath = theExportDir + "/l" + myName + ".h";
  aStream << "\nExport module to: " << theExportFilePath << std::endl;

  return true;
}

int Binder_Module::save(const std::string &theFilePath) const {
  return clang_saveTranslationUnit(myTransUnit, theFilePath.c_str(),
                                   CXSaveTranslationUnit_None);
}

bool Binder_Module::load(const std::string &theFilePath) {
  CXIndex anIndex = clang_createIndex(0, 0);
  CXTranslationUnit anTransUnit =
      clang_createTranslationUnit(anIndex, theFilePath.c_str());

  if (anTransUnit == nullptr) {
    clang_disposeTranslationUnit(anTransUnit);
    clang_disposeIndex(anIndex);
    return false;
  }

  dispose();
  myIndex = anIndex;
  myTransUnit = anTransUnit;

  return true;
}

void Binder_Module::dispose() {
  clang_disposeTranslationUnit(myTransUnit);
  clang_disposeIndex(myIndex);
}
