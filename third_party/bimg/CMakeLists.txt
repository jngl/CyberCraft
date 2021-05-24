file(GLOB_RECURSE bimg_source_files src/*)
file(GLOB_RECURSE bimg_include_files include/*)

add_library(bimg
        ${bimg_source_files}
        ${bimg_include_files})

target_include_directories(bimg PUBLIC include)
target_link_libraries(bimg bx tinyexr astc-codec lodepng stb)
