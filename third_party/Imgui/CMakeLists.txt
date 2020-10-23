file(GLOB_RECURSE Imgui_source_files src/*)
file(GLOB_RECURSE Imgui_include_files include/*)

add_library(Imgui
        ${Imgui_source_files}
        ${Imgui_include_files})

target_include_directories(Imgui PUBLIC include)
target_link_libraries(Imgui stb Glad ${SDL2_LIBRARY} )
