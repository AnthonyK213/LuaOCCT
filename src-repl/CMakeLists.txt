aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCCT_REPL_SRCS)

add_executable(
  ${PROJECT_NAME}-repl
  ${LUAOCCT_REPL_SRCS}
  )

target_link_libraries(
  ${PROJECT_NAME}-repl
  PRIVATE
  ${OpenCASCADE_LIBRARIES}
  ${LUA_LIBRARIES}
  )

add_dependencies(
  ${PROJECT_NAME}-repl
  luaocct
  )

add_custom_command(
  TARGET ${PROJECT_NAME}-repl POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "$<TARGET_PROPERTY:luaocct,BINARY_DIR>/$<CONFIG>"
    "$<TARGET_PROPERTY:luaocct-repl,BINARY_DIR>/$<CONFIG>"
  )
