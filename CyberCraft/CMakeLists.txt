add_subdirectory(lib)
add_subdirectory(defaultPlatform)

add_executable(CyberCraft src/main.cpp)
target_link_libraries(CyberCraft libCyberCraft defaultPlatform)
