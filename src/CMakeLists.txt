set(CMAKE_SHARED_LIBRARY_PREFIX "")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCCT_SRCS)

add_library(
  luaocct
  SHARED
  ${LUAOCCT_SRCS}
  )

target_link_libraries(
  luaocct
  PRIVATE
  ${OpenCASCADE_LIBRARIES}
  ${LUA_LIBRARIES}
  )
