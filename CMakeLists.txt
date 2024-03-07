cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_PREFIX_PATH "$ENV{OCCT_DIR}/lib/cmake/opencascade")

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

add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory 
  (or any directory with a CMakeLists.txt file). Please make a 
  build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# option(ENABLE_UNIT_TESTS "Enable unit tests" OFF)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

set(LUAJIT_DIR ${CMAKE_BINARY_DIR}/deps/LuaJIT_Source CACHE STRING "Path of LuaJIT 2.1 source dir")
set(LUAJIT_BUILD_EXE ON CACHE BOOL "")
option(LUAOCCT_BINDER_SUPPRESS_REGENERATION "Suppress regeneration of LuaOCCT-binder" ON)

include(cmake/FetchBinder.cmake)
include(cmake/FetchLuaBridge3.cmake)
include(cmake/FetchLuaJIT.cmake)

find_package(OpenCASCADE COMPONENTS FoundationClasses REQUIRED)
find_package(OpenCASCADE COMPONENTS ModelingAlgorithms REQUIRED)
find_package(OpenCASCADE COMPONENTS ModelingData REQUIRED)
find_package(OpenCASCADE COMPONENTS DataExchange REQUIRED)
find_package(OpenCASCADE COMPONENTS Visualization REQUIRED)
message("OCC-Include-Dir: ${OpenCASCADE_INCLUDE_DIR}")
message("OCC-Lib-Dir: ${OpenCASCADE_LIBRARY_DIR}")
message("OCC-Libs: ${OpenCASCADE_LIBRARIES}")

message("binder_SOURCE_DIR: ${binder_SOURCE_DIR}")
message("binder_BINARY_DIR: ${binder_BINARY_DIR}")
message("luajit_SOURCE_DIR: ${luajit_SOURCE_DIR}")
message("luajit_BINARY_DIR: ${luajit_BINARY_DIR}")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/include/luaocct/
  ${OpenCASCADE_INCLUDE_DIR}
  ${luabridge3_SOURCE_DIR}/Source
  ${luajit_BINARY_DIR}
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
