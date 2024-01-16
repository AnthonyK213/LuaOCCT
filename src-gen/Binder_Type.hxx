#ifndef _LuaOCCT_Binder_Type_HeaderFile
#define _LuaOCCT_Binder_Type_HeaderFile

#include <clang-c/Index.h>

#include <string>

class Binder_Cursor;

class Binder_Type {
public:
  Binder_Type(const CXType &theType);

  ~Binder_Type();

  operator CXType() { return myType; }

  std::string Spelling() const;

  CXTypeKind Kind() const { return myType.kind; }

  bool IsNull() const { return Kind() == CXType_Invalid; }

  bool IsRecord() const { return Kind() == CXType_Record; }

  bool IsTypeDef() const { return Kind() == CXType_Typedef; }

  bool IsPointer() const { return Kind() == CXType_Pointer; }

  bool IsLvalue() const { return Kind() == CXType_LValueReference; }

  bool IsRvalue() const { return Kind() == CXType_RValueReference; }

  bool IsPointerLike() const { return IsPointer() || IsLvalue() || IsRvalue(); }

  bool IsArrayLike() const {
    return Kind() == CXType_ConstantArray || Kind() == CXType_IncompleteArray ||
           Kind() == CXType_VariableArray ||
           Kind() == CXType_DependentSizedArray;
  }

  bool IsConstQualified() const { return clang_isConstQualifiedType(myType); }

  Binder_Cursor GetDeclaration() const;

  Binder_Type GetCanonical() const { return clang_getCanonicalType(myType); }

  Binder_Type GetPointee() const { return clang_getPointeeType(myType); }

private:
  CXType myType;
};

#endif
