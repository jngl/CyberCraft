cmake_minimum_required(VERSION 3.16)
project(CyberCraft)

set(CMAKE_CXX_STANDARD 17)

#SFML
find_package(SFML 2 COMPONENTS system window graphics network audio)

#SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

add_subdirectory(third_party)
add_subdirectory(LibCyberCraftCore)
add_subdirectory(LibCyberCraftSFML)
add_subdirectory(LibCyberCraftSystem)
add_subdirectory(Cyber-Engine)

file(GLOB_RECURSE CyberCraft_source_files src/*)
add_executable(CyberCraft ${CyberCraft_source_files})
target_link_libraries(CyberCraft LibCyberCraftCore LibCyberCraftSFML)
target_include_directories(CyberCraft PUBLIC src)

add_subdirectory(test)