enable_testing()

file(GLOB_RECURSE CyberCraftTest_source_files src/*)
add_executable(CyberCraftTest ${CyberCraftTest_source_files} src/Test_BTreePlus.cpp)

target_link_libraries(CyberCraftTest LibCyberCraft catch)