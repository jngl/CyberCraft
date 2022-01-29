cmake_minimum_required(VERSION 3.15)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

project(CyberCraft CXX)

include(FindPkgConfig)

option(ENABLE_TESTING "Enable Testing" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

option(ENABLE_UNITY "Enable Unity builds of projects" OFF)
if(ENABLE_UNITY)
  # Add for any project you want to apply unity builds for
  set_target_properties(intro PROPERTIES UNITY_BUILD ON)
endif()

##### TODO #####

#SFML
find_package(SFML 2 COMPONENTS system window graphics network audio)

#OpenGL
find_package(OpenGL REQUIRED)

#FMT
find_package(fmt REQUIRED)

#Sdl
pkg_search_module(SDL2 REQUIRED sdl2)

#Game dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Game)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Game)

add_subdirectory(Demo)
add_subdirectory(third_party)
add_subdirectory(Lib)
add_subdirectory(CyberEngine)
add_subdirectory(Prototype)
