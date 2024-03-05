include(FetchContent)

FetchContent_Declare(
  binder
  GIT_REPOSITORY https://github.com/AnthonyK213/LuaOCCT-binder
  GIT_TAG origin/master
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/binder
  )

# FetchContent_MakeAvailable(binder)
if(NOT binder_POPULATED)
  FetchContent_Populate(binder)
  add_subdirectory(
    ${binder_SOURCE_DIR}
    ${binder_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()
