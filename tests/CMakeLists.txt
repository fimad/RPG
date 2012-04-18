FIND_PACKAGE(CxxTest)
INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR} tests/)

macro(make_test _name _header)
  CXXTEST_ADD_TEST(${_name} ${_name}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${_header})
  target_link_libraries(${_name} barrel-lib)
endmacro(make_test)

make_test(test_res_path resources/test_path.hpp)
make_test(test_res_dir_prov resources/test_directory_provider.hpp)

