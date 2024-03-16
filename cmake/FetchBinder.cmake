include(FetchContent)

if (DEFINED ENV{LUAOCCT_BINDER_DIR})
  FetchContent_Declare(
    binder
    SOURCE_DIR $ENV{LUAOCCT_BINDER_DIR}
    )
  message("Use local LuaOCCT-binder: $ENV{LUAOCCT_BINDER_DIR}")
else()
  FetchContent_Declare(
    binder
    GIT_REPOSITORY https://github.com/AnthonyK213/LuaOCCT-binder
    GIT_TAG origin/master
    SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/binder
    )
endif()

# FetchContent_MakeAvailable(binder)
FetchContent_GetProperties(binder)
if(NOT binder_POPULATED)
  FetchContent_Populate(binder)
  add_subdirectory(
    ${binder_SOURCE_DIR}
    ${binder_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()
