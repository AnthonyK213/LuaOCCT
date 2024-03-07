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
