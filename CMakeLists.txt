cmake_minimum_required(VERSION 3.16)
project(CyberCraft)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics network audio)

add_executable(CyberCraft src/main.cpp)
target_link_libraries(CyberCraft ${SFML_LIBRARIES})