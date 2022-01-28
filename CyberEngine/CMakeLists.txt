file(GLOB_RECURSE GE_source_files src/*)
add_executable(GameEngine ${GE_source_files} )

target_link_libraries(GameEngine
        LibCyberCraftKernel
        LibCyberCraftGraphics
        )
