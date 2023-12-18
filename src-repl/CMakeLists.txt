aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCC_REPL_SRCS)

add_executable(
    ${PROJECT_NAME}-repl
    ${LUAOCC_REPL_SRCS}
    )

target_link_libraries(
    ${PROJECT_NAME}-repl
    PRIVATE
    ${PROJECT_NAME}
    ${OpenCASCADE_LIBRARIES}
    ${LUA_LIBRARIES}
    )
