file(GLOB_RECURSE demo_source_files src/*)
add_library(Demo SHARED ${demo_source_files})
target_link_libraries(Demo
        LibCyberCraftCore)