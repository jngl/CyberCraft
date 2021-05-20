file(GLOB_RECURSE libsquish_source_files src/*)
file(GLOB_RECURSE libsquish_include_files include/*)

add_library(libsquish
        ${libsquish_source_files}
        ${libsquish_include_files})

target_include_directories(libsquish PUBLIC include)
target_include_directories(libsquish PRIVATE include/libsquish/)
