#GameEngine
file(GLOB_RECURSE GE_source_files src/*)
add_executable(GameEngine ${GE_source_files} )
target_include_directories(GameEngine PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(GameEngine
        LibCyberCraftCore
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES})
