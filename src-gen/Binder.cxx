#include "Binder_Generator.hxx"

#include <sstream>

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    std::cerr << "Args?\n";
    return 1;
  }

  Binder_Generator aGenerator{};

  // std::vector<std::string> aWin32Args = {"-fms-compatibility",
  //                                        "-fms-extensions",
  //                                        "-fms-compatibility-version=19",
  //                                        "-fdelayed-template-parsing",
  //                                        "-DWNT",
  //                                        "-DWIN32",
  //                                        "-D_WINDOWS"};

  aGenerator.SetModName("Geom")
      .SetModDir(argv[2])
      .SetOcctIncDir(argv[1])
      .SetClangArgs({"-x", "c++", "-std=c++11", "-D__CODE_GENERATOR__",
                     "-Wno-deprecated-declarations", "-ferror-limit=0",
                     "-DCSFDB", "-DHAVE_CONFIG_H"});

  if (!aGenerator.Parse()) {
    return 1;
  }

  if (!aGenerator.Generate()) {
    return 2;
  }

  return 0;
}
