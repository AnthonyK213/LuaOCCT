#include "Binder_Cursor.hxx"

#include <algorithm>

Binder_Cursor::Binder_Cursor(const CXCursor &theCursor) : myCursor(theCursor) {}

Binder_Cursor::~Binder_Cursor() {}

std::vector<Binder_Cursor> Binder_Cursor::getChildren() const {
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
Binder_Cursor::getChildrenOfKind(CXCursorKind theKind,
                                 bool thePublicOnly) const {
  std::vector<Binder_Cursor> aChildren = getChildren();
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
