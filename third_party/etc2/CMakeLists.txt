file(GLOB_RECURSE etc2_source_files src/*)
file(GLOB_RECURSE etc2_include_files include/*)

add_library(etc2
        ${etc2_source_files}
        ${etc2_include_files})

target_include_directories(etc2 PUBLIC include)
target_include_directories(etc2 PRIVATE include/etc2)

target_link_libraries(etc2 bx)