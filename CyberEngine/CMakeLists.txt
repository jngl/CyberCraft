find_package(X11 REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE GE_source_files src/*)
add_executable(GameEngine ${GE_source_files} )

target_include_directories(GameEngine PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${X11_INCLUDE_DIR})

target_link_libraries(GameEngine
        LibCyberCraftCore
        LibCyberCraftKernel
        ${SDL2_LIBRARIES}
        bgfx
        ${X11_LIBRARIES}
        Threads::Threads)
