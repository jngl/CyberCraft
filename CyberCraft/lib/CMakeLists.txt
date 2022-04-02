file(GLOB_RECURSE libCyberCraft_source_files src/*)
file(GLOB_RECURSE libCyberCraft_include_files include/*)

add_library(libCyberCraft
        ${libCyberCraft_source_files}
        ${libCyberCraft_include_files})

target_include_directories(libCyberCraft PUBLIC include)
target_link_libraries(libCyberCraft project_options project_warnings CyberBase)
