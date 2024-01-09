#include "Binder_Cursor.hxx"

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    std::cerr << "Args?\n";
    return 1;
  }

  const char *cmd[5] = {"-x", "c++", "-std=c++11", "-I", argv[1]};
  const char *mod_header = argv[2];

  std::ostringstream oss{};
  oss << mod_header << '/' << "_gp.h";

  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit unit = clang_parseTranslationUnit(
      index, oss.str().c_str(), cmd, 5, nullptr, 0, CXTranslationUnit_None);

  if (unit == nullptr) {
    std::cerr << "Unable to parse translation unit. Quitting.\n";
    return 1;
  }

  CXCursor cursor = clang_getTranslationUnitCursor(unit);

  clang_visitChildren(
      cursor,
      [](CXCursor current_cursor, CXCursor parent, CXClientData client_data) {
        CXString cursor_info_str = clang_getCursorSpelling(current_cursor);
        std::string cursor_info{clang_getCString(cursor_info_str)};

        if (cursor_info.rfind("gp", 0) == 0 &&
            clang_getCursorKind(current_cursor) == CXCursor_ClassDecl) {
          std::cout << cursor_info << '\n';
        }

        clang_disposeString(cursor_info_str);

        return CXChildVisit_Continue;
      },
      nullptr);

  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);

  return 0;
}
