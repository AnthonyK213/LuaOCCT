cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

if(UNIX)
  list(APPEND CMAKE_PREFIX_PATH "$ENV{OCCT_DIR}/lib/cmake/opencascade")
endif()

project(
  luaocct
  VERSION 0.0.1
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION})

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory 
  (or any directory with a CMakeLists.txt file). Please make a 
  build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

option(ENABLE_UNIT_TESTS "Enable unit tests" OFF)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

find_package(OpenCASCADE COMPONENTS FoundationClasses REQUIRED)
find_package(OpenCASCADE COMPONENTS ModelingAlgorithms REQUIRED)
find_package(OpenCASCADE COMPONENTS ModelingData REQUIRED)
find_package(OpenCASCADE COMPONENTS DataExchange REQUIRED)
find_package(OpenCASCADE COMPONENTS Visualization REQUIRED)

message("OCC-Include-Dir: ${OpenCASCADE_INCLUDE_DIR}")
message("OCC-Lib-Dir: ${OpenCASCADE_LIBRARY_DIR}")
message("OCC-Libs: ${OpenCASCADE_LIBRARIES}")

find_package(LuaJIT REQUIRED)
message("LuaJIT-Include-Dir: ${LUA_INCLUDE_DIR}")
message("LuaJIT-Libs: ${LUA_LIBRARIES}")

find_path(LuaBridge3_INCLUDE_DIR NAMES LuaBridge PATH_SUFFIXES luabridge3)
message("LuaBridge3-Include-Dir: ${LuaBridge3_INCLUDE_DIR}")

include_directories(
  ${OpenCASCADE_INCLUDE_DIR}
  ${LUA_INCLUDE_DIR}
  ${LuaBridge3_INCLUDE_DIR}
  )

link_directories(
  ${OpenCASCADE_LIBRARY_DIR}
  )

add_subdirectory(binder/LuaOCCT-binder)
add_subdirectory(src)
add_subdirectory(src-repl)

if(ENABLE_UNIT_TESTS)
  enable_testing()
  add_subdirectory(src-test)
endif()
