file(GLOB_RECURSE astc-codec_source_files src/*)
file(GLOB_RECURSE astc-codec_include_files include/*)

add_library(astc-codec
        ${astc-codec_source_files}
        ${astc-codec_include_files})

target_include_directories(astc-codec PUBLIC include)
target_include_directories(astc-codec PRIVATE .)