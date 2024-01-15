file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bind-gen)

execute_process(
  COMMAND ${CMAKE_BINARY_DIR}/src-gen/Debug/luaocct-gen
      ${OpenCASCADE_INCLUDE_DIR}
      ${CMAKE_SOURCE_DIR}/src/mod_header
      ${CMAKE_BINARY_DIR}/bind-gen
  )

set(CMAKE_SHARED_LIBRARY_PREFIX "")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCCT_SRCS)
aux_source_directory(${CMAKE_BINARY_DIR}/bind-gen LUAOCCT_GEN_SRCS)

add_library(
  luaocct
  SHARED
  ${LUAOCCT_SRCS}
  ${LUAOCCT_GEN_SRCS}
  )

target_include_directories(
  luaocct
  PRIVATE
  ${CMAKE_BINARY_DIR}/bind-gen
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(
  luaocct
  PRIVATE
  ${OpenCASCADE_LIBRARIES}
  ${LUA_LIBRARIES}
  )
