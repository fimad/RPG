cmake_minimum_required (VERSION 2.6)
project (Barrel)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package(SFML 2 COMPONENTS system window graphics)
find_package(SFGUI)

set(EXT_LIBS
  ${SFGUI_LIBRARY}
  ${SFML_LIBRARIES}
)

include_directories(${SFML_INCLUDE_DIR} ${SFGUI_INCLUDE_DIR})

set(SRC
  src/main.cpp
)

add_executable(barrel
  SOURCES ${SRC}
  EXTERNAL_LIBS ${EXT_LIBS}
)

