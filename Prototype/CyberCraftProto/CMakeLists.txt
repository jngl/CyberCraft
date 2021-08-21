add_subdirectory(LibCyberCraftProto)

# Generic test that uses conan libs
file(GLOB_RECURSE CyberCraftProto_source_files ./src/*)
add_executable(CyberCraftProto ${CyberCraftProto_source_files})
target_link_libraries(
  CyberCraftProto
  PRIVATE project_options
          project_warnings
          LibCyberCraftCore 
          LibCyberCraftSFML
          LibCyberCraftProto)
          
target_include_directories(CyberCraftProto PUBLIC src)
