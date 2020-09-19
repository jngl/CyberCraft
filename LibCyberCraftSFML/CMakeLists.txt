file(GLOB_RECURSE LibCyberCraftSfml_source_files src/*)
file(GLOB_RECURSE LibCyberCraftSfml_include_files include/*)

add_library(LibCyberCraftSFML
        ${LibCyberCraftSfml_source_files}
        ${LibCyberCraftSfml_include_files}
        )

target_include_directories(LibCyberCraftSFML PUBLIC include)
target_link_libraries(LibCyberCraftSFML LibCyberCraft sfml-graphics)