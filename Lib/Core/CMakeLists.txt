file(GLOB_RECURSE LibCyberCraftCore_source_files src/*)
file(GLOB_RECURSE LibCyberCraftCore_include_files include/*)

add_library(LibCyberCraftCore
        ${LibCyberCraftCore_source_files}
        ${LibCyberCraftCore_include_files})

target_include_directories(LibCyberCraftCore PUBLIC include ${fmt_INCLUDE_DIRS})
target_link_libraries(LibCyberCraftCore project_options project_warnings)
target_link_libraries(LibCyberCraftCore fmt::fmt)
set_property(TARGET LibCyberCraftCore PROPERTY POSITION_INDEPENDENT_CODE ON)