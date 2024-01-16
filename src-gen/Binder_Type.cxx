#include "Binder_Type.hxx"
#include "Binder_Cursor.hxx"
#include "Binder_Util.hxx"

Binder_Type::Binder_Type(const CXType &theType) : myType(theType) {}

Binder_Type::~Binder_Type() {}

std::string Binder_Type::Spelling() const {
  return Binder_Util_GetCString(clang_getTypeSpelling(myType));
}

Binder_Cursor Binder_Type::GetDeclaration() const {
  return clang_getTypeDeclaration(myType);
}
