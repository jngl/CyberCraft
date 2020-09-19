file(GLOB_RECURSE LibCyberCraft_source_files src/*)
file(GLOB_RECURSE LibCyberCraft_include_files include/*)

add_library(LibCyberCraft
        ${LibCyberCraft_source_files}
        ${LibCyberCraft_include_files})

target_include_directories(LibCyberCraft PUBLIC include)