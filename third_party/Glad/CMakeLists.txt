file(GLOB_RECURSE Glad_source_files src/*)
file(GLOB_RECURSE Glad_include_files include/*)

add_library(Glad
        ${Glad_source_files}
        ${Glad_include_files})

target_include_directories(Glad PUBLIC include)
target_link_libraries(Glad ${CMAKE_DL_LIBS})