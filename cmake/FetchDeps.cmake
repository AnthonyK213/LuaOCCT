include(FetchContent)

FetchContent_Declare(
  binder
  GIT_REPOSITORY https://github.com/AnthonyK213/LuaOCCT-binder
  GIT_TAG origin/master
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/binder
  )

FetchContent_Declare(
  LuaBridge3
  GIT_REPOSITORY https://github.com/kunitoki/LuaBridge3.git
  GIT_TAG origin/master
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/LuaBridge3
  )

FetchContent_Declare(
  LuaJIT_Source
  GIT_REPOSITORY https://github.com/LuaJIT/LuaJIT
  GIT_TAG origin/v2.1
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/LuaJIT_Source
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  )

FetchContent_Declare(
  LuaJIT
  GIT_REPOSITORY https://github.com/zhaozg/luajit-cmake
  GIT_TAG origin/master
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/luajit-cmake
  )

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

# FetchContent_MakeAvailable(LuaBridge3)
FetchContent_GetProperties(LuaBridge3)
if(NOT luabridge3_POPULATED)
  FetchContent_Populate(LuaBridge3)
  add_subdirectory(
    ${luabridge3_SOURCE_DIR}
    ${luabridge3_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()

# FetchContent_MakeAvailable(LuaJIT_Source)
FetchContent_GetProperties(LuaJIT_Source)
if(NOT luajit_source_POPULATED)
  FetchContent_Populate(LuaJIT_Source)
endif()

# FetchContent_MakeAvailable(LuaJIT)
FetchContent_GetProperties(LuaJIT)
if(NOT luajit_POPULATED)
  FetchContent_Populate(LuaJIT)
  add_subdirectory(
    ${luajit_SOURCE_DIR}
    ${luajit_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )

  target_include_directories(
    buildvm
    PRIVATE
    ${luajit_BINARY_DIR}
    )

  set_target_properties(libluajit PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
