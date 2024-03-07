# LuaOCCT

A LuaJIT binding for [OCCT](https://dev.opencascade.org/), powered by [LuaBridge3](https://github.com/kunitoki/LuaBridge3).

## Build
- Clone the repository
  ```sh
  git clone https://github.com/AnthonyK213/LuaOCCT
  ```
- Install dependencies
  - [Libclang](https://github.com/llvm/llvm-project)
    - Set environment variable `LIBCLANG_DIR`
  - [OCCT](https://github.com/Open-Cascade-SAS/OCCT) >= 7.6.0
    - Set environment variable `OCCT_DIR`
- Build [LuaOCCT-binder](https://github.com/AnthonyK213/LuaOCCT-binder)
- Configure with cmake, generate source files.
- Build.
