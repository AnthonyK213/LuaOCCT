set(BINDER_GEN_DIR ${CMAKE_BINARY_DIR}/binder-gen)
file(MAKE_DIRECTORY ${BINDER_GEN_DIR})

function(FIND_BINDER_EXEC_ CUR_DIR_ RESULT_)
  if(WIN32)
    set(BINDER_EXEC_ luaocct-binder.exe)
  else()
    set(BINDER_EXEC_ luaocct-binder)
  endif()
  set(CANDS_ ${CUR_DIR_} ${CUR_DIR_}/Release ${CUR_DIR_}/RelWithDebInfo ${CUR_DIR_}/Debug)
  foreach(CAND_ ${CANDS_})
    set(BINDER_EXEC_PATH_ ${CAND_}/${BINDER_EXEC_})
    if(IS_DIRECTORY ${CAND_} AND EXISTS ${BINDER_EXEC_PATH_} AND NOT IS_DIRECTORY ${BINDER_EXEC_PATH_})
      set(${RESULT_} ${BINDER_EXEC_PATH_} PARENT_SCOPE)
      return()
    endif()
  endforeach()
  set(${RESULT_} ${CUR_DIR_}/${BINDER_EXEC_} PARENT_SCOPE)
endfunction()

FIND_BINDER_EXEC_(${binder_BINARY_DIR}/src/ BINDER_EXEC)
message("BINDER_EXEC: ${BINDER_EXEC}")

execute_process(
  COMMAND ${BINDER_EXEC}
      ${OpenCASCADE_INCLUDE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/../include/luaocct/mod_header
      ${BINDER_GEN_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/binder.toml
  )

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCCT_SRCS)
aux_source_directory(${BINDER_GEN_DIR} LUAOCCT_GEN_SRCS)

add_library(
  luaocct
  SHARED
  ${LUAOCCT_SRCS}
  ${LUAOCCT_GEN_SRCS}
  )

target_compile_options(
  luaocct
  PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
  $<$<CXX_COMPILER_ID:GNU>:-Wa,-mbig-obj>
  )

add_dependencies(luaocct luaocct-binder)

target_include_directories(
  luaocct
  PRIVATE
  ${BINDER_GEN_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(
  luaocct
  PRIVATE
  ${OpenCASCADE_LIBRARIES}
  PkgConfig::LuaJIT
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
  DIRECTORY ${BINDER_GEN_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/../include/luaocct/
  DESTINATION include/luaocct
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
