file(GLOB_RECURSE astc_source_files src/*)
file(GLOB_RECURSE astc_include_files include/*)

add_library(astc
        ${astc_source_files}
        ${astc_include_files})

target_include_directories(astc PUBLIC include)
target_include_directories(astc PRIVATE src)
