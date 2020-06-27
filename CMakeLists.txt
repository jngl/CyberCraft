cmake_minimum_required(VERSION 3.16)
project(CyberCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS system window graphics network audio)

add_executable(CyberCraft
        src/BasicWorld/Camera.cpp
        src/Core/Error.cpp
        src/main.cpp
        src/Game/MyPlayer.cpp
        src/Game/Tile.cpp
        src/Game/MyTileMap.cpp
        src/Game/TileObject.cpp
        src/Game/MyTileTypeRegistry.cpp
        src/BasicWorld/Player.h src/BasicWorld/Map.h src/BasicWorld/Map.cpp src/Core/Common.h)
target_link_libraries(CyberCraft sfml-graphics)