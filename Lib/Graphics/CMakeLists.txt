find_package(X11 REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE LibCyberCraftGraphics_source_files src/*)
file(GLOB_RECURSE LibCyberCraftGraphics_include_files include/*)

add_library(LibCyberCraftGraphics
        ${LibCyberCraftGraphics_source_files}
        ${LibCyberCraftGraphics_include_files})

target_include_directories(LibCyberCraftGraphics PUBLIC
        include
        ${X11_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIRS})

target_link_libraries(LibCyberCraftGraphics
        LibCyberCraftPorts
        bgfx
        ${X11_LIBRARIES}
        Threads::Threads
        ${SDL2_LIBRARIES})
