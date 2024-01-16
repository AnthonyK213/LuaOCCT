#include "Binder_Module.hxx"
#include "Binder_Generator.hxx"
#include "Binder_Util.hxx"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
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

static bool generateCtor(const Binder_Cursor &theClass,
                         std::ostream &theStream) {
  if (theClass.IsAbstract())
    return true;

  std::string aClassSpelling = theClass.Spelling();
  bool needsDefaultCtor = theClass.NeedsDefaultCtor();

  std::vector<Binder_Cursor> aCtors =
      theClass.GetChildrenOfKind(CXCursor_Constructor, true);

  // if no public ctor but non-public, do not bind any ctor.
  if (aCtors.empty() && !needsDefaultCtor)
    return true;

  if (theClass.IsTransient()) {
    // Intrusive container is gooooooooooooooooooooooooood!
    theStream << ".addConstructorFrom<opencascade::handle<" << aClassSpelling
              << ">, ";
  } else {
    theStream << ".addConstructor<";
  }

  if (needsDefaultCtor) {
    theStream << "void()";
  } else {
    theStream << Binder_Util_Join(
        aCtors.cbegin(), aCtors.cend(), [](const Binder_Cursor &theCtor) {
          std::ostringstream oss{};
          oss << "void(";
          std::vector<Binder_Cursor> aParams = theCtor.Parameters();
          oss << Binder_Util_Join(aParams.cbegin(), aParams.cend(),
                                  [](const Binder_Cursor &theParam) {
                                    return theParam.Type().Spelling();
                                  })
              << ')';
          return oss.str();
        });
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

  // FIXME: Poly_Trangulation::createNewEntity is public??????????
  // This is a workaround, since OCCT made a public cxxmethod's first
  // character capitalized.
  if (!std::isupper(aFuncSpelling.c_str()[0]))
    return true;

  // Any one uses these methods?
  if (aFuncSpelling == "DumpJson" || aFuncSpelling == "get_type_name" ||
      aFuncSpelling == "get_type_descriptor") {
    return true;
  }

  // TODO: Operator overload
  if (aFuncSpelling.rfind("operator", 0) == 0)
    return true;

  return false;
}

static bool generateMethods(const Binder_Cursor &theClass,
                            std::ostream &theStream) {
  std::string aClassSpelling = theClass.Spelling();
  std::vector<Binder_Cursor> aMethods =
      theClass.GetChildrenOfKind(CXCursor_CXXMethod);

  std::map<std::string, std::vector<Binder_Cursor>> aGroups{};
  std::map<std::string, int> aOverloads{};

  // Group cxxmethods by name.
  // An "ignored" method only increases the count in `aOverloads`, but won't be
  // added to `aGroups`.
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

  // Bind methods.
  for (auto anIter = aGroups.cbegin(); anIter != aGroups.cend(); ++anIter) {
    const std::vector<Binder_Cursor> aMethodGroup = anIter->second;

    if (aMethodGroup.empty())
      continue;

    theStream << '.'
              << (aMethodGroup[0].IsStaticMethod() ? "addStaticFunction"
                                                   : "addFunction")
              << "(\"" << anIter->first << "\", ";

    if (aMethodGroup.size() == 1 &&
        aOverloads[anIter->first] ==
            1) { /* Make sure there is no any overload method */
      theStream << '&' << aClassSpelling << "::" << anIter->first;
    } else { /* Handle the overloads */
      theStream << Binder_Util_Join(
          aMethodGroup.cbegin(), aMethodGroup.cend(),
          [&](const Binder_Cursor &theMethod) {
            std::ostringstream oss{};
            oss << "luabridge::overload<";
            std::vector<Binder_Cursor> aParams = theMethod.Parameters();
            oss << Binder_Util_Join(aParams.cbegin(), aParams.cend(),
                                    [](const Binder_Cursor &theParam) {
                                      return theParam.Type().Spelling();
                                    });
            oss << ">(&" << aClassSpelling << "::" << anIter->first << ')';
            return oss.str();
          });
    }

    theStream << ")\n";
  }

  // DownCast from Standard_Transient
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

  // The header file.
  std::ofstream aStream{theExportName + ".h"};
  std::string aGuard = "_LuaOCCT_l" + myName + "_HeaderFile";
  aStream << "#ifndef " << aGuard << "\n#define " << aGuard << '\n';
  aStream << "#include <lbind.h>\n";
  aStream << "void luaocct_init_" << myName << "(lua_State *L);\n";
  aStream << "#endif\n";

  // The source file.
  aStream = std::ofstream(theExportName + ".cpp");
  std::vector<Binder_Cursor> aClasses =
      aCursor.GetChildrenOfKind(CXCursor_ClassDecl);

  aStream << "#include \"l" << myName << ".h\"\n\n";
  aStream << "void luaocct_init_" << myName << "(lua_State *L) {\n";
  aStream << "luabridge::getGlobalNamespace(L)\n";
  aStream << ".beginNamespace(\"LuaOCCT\")\n";
  aStream << ".beginNamespace(\"" << myName << "\")\n\n";
  
  // TODO: Bind enumerators.

  // Bind classes.
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

  aStream << ".endNamespace()\n.endNamespace();\n}\n";
  std::cout << "Module exported: " << theExportName << '\n' << std::endl;

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
