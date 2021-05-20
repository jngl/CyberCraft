file(GLOB_RECURSE lodepng_source_files src/*)
file(GLOB_RECURSE lodepng_include_files include/*)

add_library(lodepng
        ${lodepng_source_files}
        ${lodepng_include_files})

target_include_directories(lodepng PUBLIC include)
target_include_directories(lodepng PRIVATE src)
