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
<<<<<<< HEAD
        LibCyberCraftKernel
=======
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
        ${SDL2_LIBRARIES}
        bgfx
        ${X11_LIBRARIES}
        Threads::Threads)
