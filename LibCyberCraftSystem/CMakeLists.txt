file(GLOB_RECURSE LibCyberCraftSystem_source_files src/*)
file(GLOB_RECURSE LibCyberCraftSystem_include_files include/*)

add_library(LibCyberCraftSystem
        ${LibCyberCraftSystem_source_files}
        ${LibCyberCraftSystem_include_files}
        )

target_include_directories(LibCyberCraftSystem PUBLIC include)
target_include_directories(LibCyberCraftSystem PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(LibCyberCraftSystem
        LibCyberCraftCore
        ${SDL2_LIBRARIES}
        Glad
        Imgui
        ${CMAKE_DL_LIBS})

