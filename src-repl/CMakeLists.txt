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
