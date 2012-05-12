cmake_minimum_required (VERSION 2.6)
project (Barrel)

ENABLE_TESTING()
set(CMAKE_BUILD_TYPE Debug)
SET(CXXTEST_USE_PYTHON TRUE)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(SFML 2 COMPONENTS system window graphics)
find_package(SFGUI)
find_package(Lua51)

#hack to easily compile with SLB on my system
set(SLB_LIBRARY ${PROJECT_SOURCE_DIR}/../slb/build/bin/static/libSLB.a)
set(SLB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../slb/include)

set(RAPIDXML_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../rapidxml-1.13)

set(EXT_LIBS
  ${SFGUI_LIBRARY}
  ${SFML_LIBRARIES}
  ${LUA_LIBRARY}
  ${SLB_LIBRARY}
)

include_directories(
  ${SFML_INCLUDE_DIR}
  ${SFGUI_INCLUDE_DIR}
  ${LUA_INCLUDE_DIR}
  ${SLB_INCLUDE_DIR}
  ${RAPIDXML_INCLUDE_DIR}
  src/
)

add_subdirectory(tests) #all of our unit tests!
add_subdirectory(tools) #random tools

set(SRC
  src/Errors.hpp
  src/Errors.cpp

  src/resources/Path.hpp
  src/resources/Path.cpp
  src/resources/Resource.hpp
  src/resources/Resource.cpp
  src/resources/XmlResource.hpp
  src/resources/XmlResource.cpp
  src/resources/ResourceDefs.hpp
  src/resources/ResourceDefs.cpp
  src/resources/ResourceManager.hpp
  src/resources/ResourceManager.cpp
  src/resources/ResourceProvider.hpp
  src/resources/DirectoryProvider.hpp
  src/resources/DirectoryProvider.cpp

  src/scripting/EventManager.hpp
  src/scripting/EventManager.cpp
  src/scripting/EventHandler.hpp
  src/scripting/GenericEvent.hpp
  src/scripting/GenericEvent.cpp
  src/scripting/StringEvent.hpp
  src/scripting/StringEvent.cpp
  src/scripting/EventRaiser.hpp
  src/scripting/EventRaiser.cpp
  src/scripting/LuaWrapper.hpp
  src/scripting/LuaWrapper.cpp
  src/scripting/LuaErrors.hpp
  src/scripting/LuaErrors.cpp
  src/scripting/Condition.hpp
  src/scripting/Condition.cpp
  src/scripting/GuardedObject.hpp
  src/scripting/GuardedObject.cpp
  src/scripting/GuardedList.hpp

  src/plot/DialogueList.hpp
  src/plot/DialogueList.cpp
  src/plot/DialogueNode.hpp
  src/plot/DialogueNode.cpp
  src/plot/DialogueEvent.hpp
  src/plot/DialogueEvent.cpp
  src/plot/DialogueRunner.hpp
  src/plot/DialogueRunner.cpp

  src/character/Character.hpp
  src/character/Character.cpp
  src/character/Race.hpp
  src/character/Race.cpp
  src/character/CharacterClass.hpp
  src/character/CharacterClass.cpp
  src/character/Stats.hpp
  src/character/Stats.cpp
  src/character/Modifier.hpp
  src/character/Modifier.cpp
  src/character/ProxyModifier.hpp
  src/character/ProxyModifier.cpp
  src/character/Item.hpp
  src/character/Item.cpp

  src/map/Map.hpp
  src/map/Map.cpp
  src/map/Tile.hpp
  src/map/Tile.cpp
  src/map/TileEvent.hpp
  src/map/TileEvent.cpp
  src/map/Direction.hpp
  src/map/MapContents.hpp
  src/map/MapContents.cpp

  src/game/Die.hpp
  src/game/Die.cpp
)

add_library(barrel-lib
  ${SRC}
)

add_executable(barrel
  src/main.cpp
)
target_link_libraries(barrel barrel-lib ${EXT_LIBS})

