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

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )

install(
  DIRECTORY ${CMAKE_BINARY_DIR}/bind-gen/ ${CMAKE_CURRENT_SOURCE_DIR}/
  DESTINATION include
  COMPONENT header_files
  FILES_MATCHING PATTERN "*.h"
  )

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION lib/cmake/luaocct
  )

set(INCLUDE_DIR include)
set(LIBRARIES ${PROJECT_NAME})
set(LIBRARY_DIR lib)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION 0.0.1
  COMPATIBILITY SameMajorVersion
  )

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION lib/cmake/luaocct
  PATH_VARS INCLUDE_DIR LIBRARIES LIBRARY_DIR
  INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
  )

install(
  FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION lib/cmake/luaocct
  )
