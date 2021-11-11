file(GLOB_RECURSE Ports_source_files src/*)
file(GLOB_RECURSE Ports_include_files include/*)

add_library(LibCyberCraftPorts
        ${Ports_source_files}
        ${Ports_include_files})

target_include_directories(LibCyberCraftPorts PUBLIC include)
target_link_libraries(LibCyberCraftPorts project_options project_warnings LibCyberCraftCore)