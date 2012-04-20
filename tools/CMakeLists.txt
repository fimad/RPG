INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR} tests/ .)

macro(make_tool _name _files)
  add_executable(${_name}
    ${_files}
  )
  target_link_libraries(${_name} barrel-lib ${EXT_LIBS})
endmacro(make_tool)

make_tool(dialogue-runner plot/dialogue-runner.cpp)
