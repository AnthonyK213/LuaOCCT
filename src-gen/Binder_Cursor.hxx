#ifndef _LuaOCCT_Binder_Cursor_HeaderFile
#define _LuaOCCT_Binder_Cursor_HeaderFile

#include "Binder_Type.hxx"
#include "Binder_Util.hxx"

#include <vector>

class Binder_Cursor {
public:
  Binder_Cursor(const CXCursor &theCursor);

  ~Binder_Cursor();

  CXCursorKind Kind() const { return clang_getCursorKind(myCursor); }

  Binder_Type Type() const { return clang_getCursorType(myCursor); }

  Binder_Type ReturnType() const {
    return clang_getResultType(clang_getCursorType(myCursor));
  }

  std::string Spelling() const {
    return Binder_Util_GetCString(clang_getCursorSpelling(myCursor));
  }

  bool NoDecl() const { return Kind() == CXCursor_NoDeclFound; }

  bool IsNull() const { return clang_Cursor_isNull(myCursor) || NoDecl(); }

  bool IsTransUnit() const { return Kind() == CXCursor_TranslationUnit; }

  bool IsEnum() const { return Kind() == CXCursor_EnumDecl; }

  bool IsEnumConst() const { return Kind() == CXCursor_EnumConstantDecl; }

  bool IsFunction() const { return Kind() == CXCursor_FunctionDecl; }

  bool IsClass() const {
    return Kind() == CXCursor_ClassDecl || Kind() == CXCursor_StructDecl;
  }

  bool IsTypeDef() const { return Kind() == CXCursor_TypedefDecl; }

  bool IsCxxBase() const { return Kind() == CXCursor_CXXBaseSpecifier; }

  bool IsCtor() const { return Kind() == CXCursor_Constructor; }

  bool IsDtor() const { return Kind() == CXCursor_Destructor; }

  bool IsCxxMethod() const { return Kind() == CXCursor_CXXMethod; }

  bool IsParam() const { return Kind() == CXCursor_ParmDecl; }

  bool IsField() const { return Kind() == CXCursor_FieldDecl; }

  bool IsTemplateRef() const { return Kind() == CXCursor_TemplateRef; }

  bool IsClassTemplate() const { return Kind() == CXCursor_ClassTemplate; }

  bool IsFunctionTemplate() const {
    return Kind() == CXCursor_FunctionTemplate;
  }

  bool IsTemplateTypeParam() const {
    return Kind() == CXCursor_TemplateTypeParameter;
  }

  bool IsUsingDecl() const { return Kind() == CXCursor_UsingDeclaration; }

  bool IsOverloadedDeclRef() const {
    return Kind() == CXCursor_OverloadedDeclRef;
  }

  bool IsCxxAccessSpec() const { return Kind() == CXCursor_CXXAccessSpecifier; }

  bool IsTypeRef() const { return Kind() == CXCursor_TypeRef; }

  bool IsPublic() const { return !(IsPrivate() || IsProtected()); }

  bool IsPrivate() const {
    return clang_getCXXAccessSpecifier(myCursor) == CX_CXXPrivate;
  }

  bool IsProtected() const {
    return clang_getCXXAccessSpecifier(myCursor) == CX_CXXProtected;
  }

  bool IsDefinition() const { return clang_isCursorDefinition(myCursor); }

  bool IsVirtualMethod() const { return clang_CXXMethod_isVirtual(myCursor); }

  bool IsPureVirtualMethod() const {
    return clang_CXXMethod_isPureVirtual(myCursor);
  }

  bool IsAbstract() const { return clang_CXXRecord_isAbstract(myCursor); }

  bool IsConstMethod() const { return clang_CXXMethod_isConst(myCursor); }

  bool IsStaticMethod() const { return clang_CXXMethod_isStatic(myCursor); }

  bool IsMoveCtor() const {
    return clang_CXXConstructor_isMoveConstructor(myCursor);
  }

  bool IsCopyCtor() const {
    return clang_CXXConstructor_isCopyConstructor(myCursor);
  }

  bool IsDefaultCtor() const {
    return clang_CXXConstructor_isDefaultConstructor(myCursor);
  }

  bool IsAnonymous() const { return clang_Cursor_isAnonymous(myCursor); }

  bool IsTransient() const {
    if (Spelling() == "Standard_Transient")
      return true;

    // TODO: Base

    return false;
  }

  bool IsOperator() const {
    if (IsFunction() || IsCxxMethod()) {
      // TODO: Lua operator table
      return true;
    }

    return false;
  }

  Binder_Cursor Parent() const {
    return clang_getCursorSemanticParent(myCursor);
  }

  std::string Docs() const {
    return Binder_Util_GetCString(clang_Cursor_getBriefCommentText(myCursor));
  }

  std::vector<Binder_Cursor> Bases() const {
    return getChildrenOfKind(CXCursor_CXXBaseSpecifier);
  }

private:
  std::vector<Binder_Cursor> getChildren() const;

  std::vector<Binder_Cursor>
  getChildrenOfKind(CXCursorKind theKind, bool thePublicOnly = false) const;

private:
  CXCursor myCursor;
};

#endif
