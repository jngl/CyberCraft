cmake_minimum_required(VERSION 3.16)
project(CyberCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS system window graphics network audio)

add_subdirectory(third_party)
add_subdirectory(LibCyberCraftCore)
add_subdirectory(LibCyberCraftSFML)

file(GLOB_RECURSE CyberCraft_source_files src/*)
add_executable(CyberCraft ${CyberCraft_source_files})
target_link_libraries(CyberCraft LibCyberCraftCore LibCyberCraftSFML)
target_include_directories(CyberCraft PUBLIC src)

add_subdirectory(test)