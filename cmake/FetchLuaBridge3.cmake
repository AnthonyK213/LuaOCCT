include(FetchContent)

FetchContent_Declare(
  LuaBridge3
  GIT_REPOSITORY https://github.com/kunitoki/LuaBridge3.git
  GIT_TAG origin/master
  GIT_SHALLOW 1
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/LuaBridge3
  )

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
