set(CMAKE_SHARED_LIBRARY_PREFIX "")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCCT_SRCS)

add_library(
    ${PROJECT_NAME}
    SHARED
    ${LUAOCCT_SRCS}
    )

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCASCADE_LIBRARIES}
    ${LUA_LIBRARIES}
    )
