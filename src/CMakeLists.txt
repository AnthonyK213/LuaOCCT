aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCC_SRCS)

add_library(
    ${PROJECT_NAME}
    SHARED
    ${LUAOCC_SRCS}
    )

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    third_party/LuaBridge3/Source/
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCASCADE_LIBRARIES}
    ${LUA_LIBRARIES}
    )
