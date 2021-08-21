file(GLOB_RECURSE Match3_source_files src/*)

add_executable(Match3 ${Match3_source_files})
target_include_directories(Match3 PUBLIC
        ${SDL2_INCLUDE_DIRS})

target_link_libraries(Match3
        ${SDL2_LIBRARIES}
        LibCyberCraftCore)