# LuaOCCT

A LuaJIT binding for [OCCT](https://dev.opencascade.org/), powered by [LuaBridge3](https://github.com/kunitoki/LuaBridge3).

## Build
- Clone the repository
  ```sh
  git clone https://github.com/AnthonyK213/LuaOCCT
  ```
- Install dependencies
  - Install the latest release of [vcpkg](https://github.com/microsoft/vcpkg)
    - Set environment variable `VCPKG_ROOT`
  - Install `pkg-config`
    - For [windows](https://stackoverflow.com/questions/1710922/how-to-install-pkg-config-in-windows)
  - [Libclang](https://github.com/llvm/llvm-project)
    - Set environment variable `LIBCLANG_DIR`
  - [OCCT](https://github.com/Open-Cascade-SAS/OCCT) >= 7.6.0 is needed on Linux,
    since the vcpkg port on Linux is not usable.
    - Build & Install (on Linux)
    - Set environment variable `OCCT_DIR` (on Linux)
- Build [LuaOCCT-binder](https://github.com/AnthonyK213/LuaOCCT-binder)
- Configure with cmake, generate source files.
- Build.
