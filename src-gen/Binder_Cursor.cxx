#include "Binder_Cursor.hxx"

#include <algorithm>
#include <iostream>
#include <set>

Binder_Cursor::Binder_Cursor(const CXCursor &theCursor) : myCursor(theCursor) {}

Binder_Cursor::~Binder_Cursor() {}

bool Binder_Cursor::IsTransient() const {
  if (Spelling() == "Standard_Transient")
    return true;

  std::vector<Binder_Cursor> aBases = GetAllBases();

  for (const auto &aBase : aBases) {
    if (aBase.Type().Spelling() == "Standard_Transient")
      return true;
  }

  return false;
}

bool Binder_Cursor::IsOperator() const {
  if (IsFunction() || IsCxxMethod()) {
    // TODO: Lua operator table
    return true;
  }

  return false;
}

bool Binder_Cursor::IsGetterMethod() const {
  if (IsCxxMethod() && IsPublic() && ReturnType().IsLvalue()) {
    std::string aSetterName = "Set" + Spelling();

    for (const auto &aMethod : Parent().Methods()) {
      if (aMethod.Spelling() == aSetterName && aMethod.IsPublic())
        return true;
    }
  }

  return false;
}

bool Binder_Cursor::IsImmutable() const {
  Binder_Type aType = Type();

  if (aType.IsPointerLike())
    aType = aType.GetPointee();

  static std::set<std::string> immutable{"Standard_Boolean", "Standard_CString",
                                         "Standard_Integer", "Standard_Real"};

  return immutable.find(aType.Spelling()) != immutable.end();
}

bool Binder_Cursor::NeedsInOutMethod() const {
  for (auto &p : Parameters()) {
    Binder_Type aType = p.Type();

    if (/*p.IsImmutable() &&*/ !aType.IsConstQualified() &&
        aType.IsPointerLike()) {
      return true;
    }
  }

  return false;
}

bool Binder_Cursor::NeedsDefaultCtor() const {
  if (IsAbstract())
    return false;

  return Ctors().empty();

  // std::vector<Binder_Cursor> anAllBases = GetAllBases();
  // anAllBases.push_back(*this);

  // for (const auto &anItem : anAllBases) {
  //   Binder_Cursor aDef = anItem.GetDefinition();

  //   if (!aDef.Ctors().empty())
  //     return false;
  // }

  // return true;
}

static void getBases(const Binder_Cursor &theCursor,
                     std::vector<Binder_Cursor> &theBases) {
  for (const auto aBase : theCursor.Bases()) {
    theBases.push_back(aBase);
    Binder_Cursor aDecl = aBase.Type().GetDeclaration();

    if (aDecl.NoDecl())
      continue;

    if (aDecl.IsClassTemplate()) {
      getBases(aDecl, theBases);
      continue;
    }

    Binder_Cursor aSepc = aDecl.GetSpecialization();

    if (!aSepc.NoDecl() && aSepc.IsClassTemplate()) {
      getBases(aSepc, theBases);
      continue;
    }

    if (aDecl.IsClass()) {
      getBases(aDecl, theBases);
      continue;
    }

    if (aDecl.IsTypeDef()) {
      aDecl = aDecl.UnderlyingTypedefType().GetDeclaration();
      aSepc = aDecl.GetSpecialization();

      if (!aSepc.NoDecl() && aSepc.IsClassTemplate()) {
        getBases(aSepc, theBases);
      } else {
        getBases(aDecl, theBases);
      }

      continue;
    }

    std::cout << "Failed to find a base for " << aBase.Spelling() << '\n';
  }
}

std::vector<Binder_Cursor> Binder_Cursor::GetAllBases() const {
  std::vector<Binder_Cursor> aBases{};
  Binder_Cursor aSpec = GetSpecialization();

  if (!aSpec.NoDecl() && aSpec.IsClassTemplate()) {
    getBases(aSpec, aBases);
  } else {
    getBases(*this, aBases);
  }

  return aBases;
}

std::vector<Binder_Cursor> Binder_Cursor::GetChildren() const {
  std::vector<Binder_Cursor> aChildren{};

  clang_visitChildren(
      myCursor,
      [](CXCursor theCursor, CXCursor theParent, CXClientData theClientData) {
        auto aChildrenPtr =
            static_cast<std::vector<Binder_Cursor> *>(theClientData);
        aChildrenPtr->push_back(theCursor);

        return CXChildVisit_Continue;
      },
      &aChildren);

  return aChildren;
}

std::vector<Binder_Cursor>
Binder_Cursor::GetChildrenOfKind(CXCursorKind theKind,
                                 bool thePublicOnly) const {
  std::vector<Binder_Cursor> aChildren = GetChildren();
  std::vector<Binder_Cursor> aChildrenQualified{};

  std::copy_if(aChildren.cbegin(), aChildren.cend(),
               std::back_inserter(aChildrenQualified),
               [=](const Binder_Cursor &theCursor) {
                 if (theCursor.Kind() != theKind)
                   return false;

                 if (thePublicOnly && !theCursor.IsPublic())
                   return false;

                 return true;
               });

  return aChildrenQualified;
}
