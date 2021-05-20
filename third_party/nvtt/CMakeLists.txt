file(GLOB_RECURSE nvtt_source_files src/*)
file(GLOB_RECURSE nvtt_include_files include/*)

add_library(nvtt
        ${nvtt_source_files}
        ${nvtt_include_files})

target_include_directories(nvtt PUBLIC include)
target_include_directories(nvtt PRIVATE src)
target_link_libraries(nvtt bx)