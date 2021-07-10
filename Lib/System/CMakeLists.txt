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
<<<<<<< HEAD:Lib/System/CMakeLists.txt
        LibCyberCraftKernel
=======
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:LibCyberCraftSystem/CMakeLists.txt
        ${SDL2_LIBRARIES}
        Glad
        Imgui
        ${CMAKE_DL_LIBS})

