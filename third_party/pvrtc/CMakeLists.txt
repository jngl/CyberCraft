file(GLOB_RECURSE pvrtc_source_files src/*)
file(GLOB_RECURSE pvrtc_include_files include/*)

add_library(pvrtc
        ${pvrtc_source_files}
        ${pvrtc_include_files})

target_include_directories(pvrtc PUBLIC include)
target_include_directories(pvrtc PRIVATE src)
