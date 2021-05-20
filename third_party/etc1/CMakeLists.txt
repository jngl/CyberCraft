file(GLOB_RECURSE etc1_source_files src/*)
file(GLOB_RECURSE etc1_include_files include/*)

add_library(etc1
        ${etc1_source_files}
        ${etc1_include_files})

target_include_directories(etc1 PUBLIC include)
target_include_directories(etc1 PRIVATE include/etc1)