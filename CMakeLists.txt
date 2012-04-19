cmake_minimum_required (VERSION 2.6)
project (Barrel)

ENABLE_TESTING()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(SFML 2 COMPONENTS system window graphics)
find_package(SFGUI)

set(EXT_LIBS
  ${SFGUI_LIBRARY}
  ${SFML_LIBRARIES}
)

include_directories(${SFML_INCLUDE_DIR} ${SFGUI_INCLUDE_DIR} src/)

add_subdirectory(tests) #all of our unit tests!

set(SRC
  src/Errors.hpp
  src/Errors.cpp

  src/resources/Path.hpp
  src/resources/Path.cpp
  src/resources/Resource.hpp
  src/resources/Resource.cpp
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
)

add_executable(barrel
  src/main.cpp
  ${SRC}
  ${EXT_LIBS}
)

add_library(barrel-lib
  ${SRC}
  ${EXT_LIBS}
)

