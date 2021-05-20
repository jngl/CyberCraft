file(GLOB_RECURSE iqa_source_files src/*)
file(GLOB_RECURSE iqa_include_files include/*)

add_library(iqa
        ${iqa_source_files}
        ${iqa_include_files})

target_include_directories(iqa PUBLIC include)
target_include_directories(iqa PRIVATE src)
set_target_properties(iqa PROPERTIES LINKER_LANGUAGE CXX)