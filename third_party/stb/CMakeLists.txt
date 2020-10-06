file(GLOB_RECURSE stb_source_files src/*)
file(GLOB_RECURSE stb_include_files include/*)

add_library(stb
        ${stb_source_files}
        ${stb_include_files})

target_include_directories(stb PUBLIC include)