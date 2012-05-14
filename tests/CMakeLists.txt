FIND_PACKAGE(CxxTest)
INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR} tests/ .)

macro(make_test _name _header)
  CXXTEST_ADD_TEST(${_name} ${_name}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${_header})
  target_link_libraries(${_name} barrel-lib ${EXT_LIBS})
endmacro(make_test)

#Resource tests
make_test(test_res_path resources/test_path.hpp)
make_test(test_res_dir_prov resources/test_directory_provider.hpp)
#make_test(test_res_man resources/test_resource_manager.hpp)

#Scripting tests
make_test(test_scr_events scripting/test_events.hpp)
make_test(test_scr_lua scripting/test_lua.hpp)
make_test(test_scr_guards scripting/test_guards.hpp)

#Plot tests
make_test(test_plot_dialogue plot/test_dialogue.hpp)

#Character tests
make_test(test_chr_modifiers character/test_modifiers.hpp)
make_test(test_chr_race_class character/test_race_class.hpp)
make_test(test_chr_stats character/test_stats.hpp)
make_test(test_chr_character character/test_character.hpp)
make_test(test_chr_item character/test_item.hpp)
make_test(test_chr_spell character/test_spell.hpp)

#map tests
make_test(test_map map/test_map.hpp)

#game tests
make_test(test_game_die game/test_die.hpp)
