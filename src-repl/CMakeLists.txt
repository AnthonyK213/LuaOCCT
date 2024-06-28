aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LUAOCCT_REPL_SRCS)

add_executable(
  ${PROJECT_NAME}-repl
  ${LUAOCCT_REPL_SRCS}
  )

target_include_directories(
  ${PROJECT_NAME}-repl
  PRIVATE
  ${OpenCASCADE_INCLUDE_DIR}
  )

target_link_directories(
  ${PROJECT_NAME}-repl
  PRIVATE
  ${OpenCASCADE_LIBRARY_DIR}
)

if(WIN32)
  target_link_libraries(
    ${PROJECT_NAME}-repl
    PRIVATE
    ${OpenCASCADE_LIBRARIES}
    luajit::lib
    luajit::header
    )
else(WIN32)
  target_link_libraries(
    ${PROJECT_NAME}-repl
    PRIVATE
    ${OpenCASCADE_LIBRARIES}
    # https://luajit.org/install.html#:~:text=In%20the%20latter%20case%20you%27ll%20need%20to%20export%20all%20public%20symbols%20from%20your%20main%20executable
    -Wl,-E
    luajit::lib
    luajit::header
    )
endif(WIN32)

add_dependencies(
  ${PROJECT_NAME}-repl
  luaocct
  )

if(WIN32)
  add_custom_command(
    TARGET ${PROJECT_NAME}-repl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "$<TARGET_PROPERTY:luaocct,BINARY_DIR>/$<CONFIG>"
      "$<TARGET_PROPERTY:luaocct-repl,BINARY_DIR>/$<CONFIG>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${OpenCASCADE_LIBRARY_DIR}/../bin$<$<CONFIG:Debug>:d>"
      "$<TARGET_PROPERTY:${PROJECT_NAME}-repl,BINARY_DIR>/$<CONFIG>"
    )
elseif(UNIX AND NOT APPLE)
  add_custom_command(
    TARGET ${PROJECT_NAME}-repl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      "$<TARGET_PROPERTY:luaocct,BINARY_DIR>/$<CONFIG>/libluaocct.so"
      "$<TARGET_PROPERTY:luaocct-repl,BINARY_DIR>/$<CONFIG>/luaocct.so"
    )
endif()
