add_subdirectory(LibCyberCraftProto)

file(GLOB_RECURSE CyberCraftProto_source_files ./src/*)
add_executable(CyberCraftProto ${CyberCraftProto_source_files})
target_link_libraries(
  CyberCraftProto
  PRIVATE project_options
          project_warnings
          LibCyberCraftGraphics
          LibCyberCraftProto)
          
target_include_directories(CyberCraftProto PUBLIC src)
