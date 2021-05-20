file(GLOB_RECURSE edtaa3_source_files src/*)
file(GLOB_RECURSE edtaa3_include_files include/*)

add_library(edtaa3
        ${edtaa3_source_files}
        ${edtaa3_include_files})

target_include_directories(edtaa3 PUBLIC include)
target_include_directories(edtaa3 PRIVATE src)
