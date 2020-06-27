cmake_minimum_required(VERSION 3.16)
project(CyberCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS system window graphics network audio)

add_executable(CyberCraft
        src/Camera.cpp
        src/Error.cpp
        src/main.cpp
        src/Player.cpp
        src/Tile.cpp
        src/TileMap.cpp
        src/TileObject.cpp
        src/TileTypeRegistry.cpp)
target_link_libraries(CyberCraft sfml-graphics)