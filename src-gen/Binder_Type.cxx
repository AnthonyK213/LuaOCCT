#include "Binder_Type.hxx"
#include "Binder_Cursor.hxx"

Binder_Type::Binder_Type(const CXType &theType) : myType(theType) {}

Binder_Type::~Binder_Type() {}

Binder_Cursor Binder_Type::GetDeclaration() const {
  return clang_getTypeDeclaration(myType);
}
