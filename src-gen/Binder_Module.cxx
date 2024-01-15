#include "Binder_Module.hxx"
#include "Binder_Generator.hxx"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <vector>

Binder_Module::Binder_Module(const std::string &theName,
                             Binder_Generator &theParent)
    : myName(theName), myParent(&theParent), myIndex(nullptr),
      myTransUnit(nullptr) {}

Binder_Module::~Binder_Module() { dispose(); }

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
  if (theClass.IsAbstract())
    return true;

  std::string aClassSpelling = theClass.Spelling();

  std::vector<Binder_Cursor> aCtors =
      theClass.GetChildrenOfKind(CXCursor_Constructor, true);

  if (aCtors.empty())
    return true;

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
  if (theMethod.IsOverride() || !theMethod.IsPublic() ||
      theMethod.IsFunctionTemplate())
    return true;

  // TODO: IN/OUT parameter
  if (theMethod.NeedsInOutMethod())
    return true;

  std::string aFuncSpelling = theMethod.Spelling();

  // FIXME: Poly_Trangulation::createNewEntity??????????
  if (!std::isupper(aFuncSpelling.c_str()[0]))
    return true;

  if (aFuncSpelling == "DumpJson" || aFuncSpelling == "get_type_name" ||
      aFuncSpelling == "get_type_descriptor") {
    return true;
  }

  if (aFuncSpelling.rfind("operator", 0) == 0)
    return true;

  // TODO: Operator overload

  return false;
}

static bool generateMethods(const Binder_Cursor &theClass,
                            std::ostream &theStream) {
  std::string aClassSpelling = theClass.Spelling();
  std::vector<Binder_Cursor> aMethods =
      theClass.GetChildrenOfKind(CXCursor_CXXMethod);

  std::map<std::string, std::vector<Binder_Cursor>> aGroups{};
  std::map<std::string, int> aOverloads{};

  for (const auto &aMethod : aMethods) {
    std::string aFuncSpelling = aMethod.Spelling();

    if (aGroups.find(aFuncSpelling) != aGroups.end()) {
      if (!isIgnoredMethod(aMethod)) {
        aGroups[aFuncSpelling].push_back(aMethod);
      }
    } else {
      aOverloads.insert({aFuncSpelling, 0});

      if (!isIgnoredMethod(aMethod)) {
        aGroups.insert({aFuncSpelling, std::vector<Binder_Cursor>{aMethod}});
      }
    }

    aOverloads[aFuncSpelling]++;
  }

  for (auto anIter = aGroups.cbegin(); anIter != aGroups.cend(); ++anIter) {
    const std::vector<Binder_Cursor> aMethodGroup = anIter->second;
    const int aOverload = aOverloads[anIter->first];

    if (aMethodGroup.empty())
      continue;

    std::string anBindFunc =
        aMethodGroup[0].IsStaticMethod() ? "addStaticFunction" : "addFunction";

    theStream << '.' << anBindFunc << "(\"" << anIter->first << "\", ";

    if (aMethodGroup.size() == 1 && aOverload == 1) {
      theStream << '&' << aClassSpelling << "::" << anIter->first;
    } else {
      for (int anIdx = 0; anIdx < aMethodGroup.size(); ++anIdx) {
        if (anIdx > 0)
          theStream << ", ";

        theStream << "luabridge::overload<";

        std::vector<Binder_Cursor> aParams = aMethodGroup[anIdx].Parameters();

        for (int anI = 0; anI < aParams.size(); ++anI) {
          if (anI > 0)
            theStream << ", ";

          theStream << aParams[anI].Type().Spelling();
        }

        theStream << ">(&" << aClassSpelling << "::" << anIter->first << ')';
      }
    }

    theStream << ")\n";
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
  std::cout << "Binding class: " << aClassSpelling << '\n';
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
  std::string theExportName = theExportDir + "/l" + myName;

  std::ofstream aStream{theExportName + ".h"};
  std::string aGuard = "_LuaOCCT_l" + myName + "_HeaderFile";
  aStream << "#ifndef " << aGuard << "\n#define " << aGuard << '\n';
  aStream << "#include <lbind.h>\n";
  aStream << "void luaocct_init_" << myName << "(lua_State *L);\n";
  aStream << "#endif\n";

  aStream = std::ofstream(theExportName + ".cpp");
  std::vector<Binder_Cursor> aClasses =
      aCursor.GetChildrenOfKind(CXCursor_ClassDecl);

  aStream << "#include \"l" << myName << ".h\"\n\n";
  aStream << "void luaocct_init_" << myName << "(lua_State *L) {\n";
  aStream << "luabridge::getGlobalNamespace(L)\n";

  aStream << ".beginNamespace(\"LuaOCCT\")\n";
  aStream << ".beginNamespace(\"" << myName << "\")\n\n";

  for (const auto &aClass : aClasses) {
    std::string aClassSpelling = aClass.Spelling();

    if (aClassSpelling.rfind(myName, 0) != 0)
      continue;

    if (aClassSpelling.rfind("Handle", 0) == 0)
      continue;

    if (aClassSpelling.rfind("NCollection", 0) == 0)
      continue;

    if (aClassSpelling.rfind("TCol", 0) == 0)
      continue;

    if (aClassSpelling.find("Sequence") != std::string::npos)
      continue;

    if (aClassSpelling.find("Array") != std::string::npos)
      continue;

    if (aClassSpelling.find("List") != std::string::npos)
      continue;

    if (aClassSpelling == "Standard")
      continue;

    if (aClass.GetChildren().empty())
      continue;

    if (!myParent->AddVisitedClass(aClassSpelling))
      continue;

    generateClass(aClass, aStream);
  }

  aStream << ".endNamespace()\n";
  aStream << ".endNamespace();\n";
  aStream << "}";

  std::cout << "\nExport module to: " << theExportName << std::endl;

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
