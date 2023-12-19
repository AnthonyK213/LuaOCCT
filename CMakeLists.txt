cmake_minimum_required(VERSION 3.20)

if(WIN32)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(
  luaocc
  VERSION 0.0.1
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install/${CMAKE_BUILD_TYPE})

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

include(FindLuaJIT)
find_package(LuaJIT REQUIRED)

message("LuaJIT-Include-Dir: ${LUA_INCLUDE_DIR}")
message("LuaJIT-Libs: ${LUA_LIBRARIES}")

include_directories(
  ${OpenCASCADE_INCLUDE_DIR}
  ${LUA_INCLUDE_DIR}
  third_party/LuaBridge3/Source/
  )

link_directories(
  ${OpenCASCADE_LIBRARY_DIR}
  )

add_subdirectory(src)
add_subdirectory(src-repl)

if(ENABLE_UNIT_TESTS)
  enable_testing()
  add_subdirectory(src-test)
endif()
