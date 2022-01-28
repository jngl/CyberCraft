file(GLOB_RECURSE LibCyberCraftProto_source_files src/*)
file(GLOB_RECURSE LibCyberCraftProto_include_files include/*)

add_library(LibCyberCraftProto
        ${LibCyberCraftProto_source_files}
        ${LibCyberCraftProto_include_files})

target_include_directories(LibCyberCraftProto PUBLIC include)
target_link_libraries(LibCyberCraftProto project_options project_warnings LibCyberCraftKernel)