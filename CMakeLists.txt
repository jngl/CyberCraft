cmake_minimum_required(VERSION 3.16)
project(CyberCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS system window graphics network audio)

add_executable(CyberCraft
        src/Core/Common.h
        src/Core/Error.cpp
        src/Core/Error.h
        src/Core/Math.h
        src/Core/Window.cpp
        src/Core/Window.h
        src/main.cpp src/Core/Scene.cpp src/Core/Scene.h src/Core/Update.h src/Core/Update.cpp)
target_link_libraries(CyberCraft sfml-graphics)