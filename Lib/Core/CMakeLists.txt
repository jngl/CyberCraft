file(GLOB_RECURSE LibCyberCraftCore_source_files src/*)
file(GLOB_RECURSE LibCyberCraftCore_include_files include/*)

add_library(LibCyberCraftCore
        ${LibCyberCraftCore_source_files}
        ${LibCyberCraftCore_include_files})

target_include_directories(LibCyberCraftCore PUBLIC include)
target_link_libraries(LibCyberCraftCore project_options project_warnings)
