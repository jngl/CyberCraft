file(GLOB_RECURSE Kernel_source_files src/*)
file(GLOB_RECURSE Kernel_include_files include/*)

add_library(LibCyberCraftKernel
        ${Kernel_source_files}
        ${Kernel_include_files})

target_include_directories(LibCyberCraftKernel PUBLIC include)
target_link_libraries(LibCyberCraftKernel project_options project_warnings LibCyberCraftPorts)
set_property(TARGET LibCyberCraftKernel PROPERTY POSITION_INDEPENDENT_CODE ON)