set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE defaultPlatform_source_files src/*)
file(GLOB_RECURSE defaultPlatform_include_files PublicInclude/*)

add_library(defaultPlatform
        ${defaultPlatform_source_files}
        ${defaultPlatform_include_files})

target_include_directories(defaultPlatform PUBLIC
        PublicInclude
        ${X11_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIRS})
target_include_directories(defaultPlatform PRIVATE PrivateInclude)
target_link_libraries(defaultPlatform
        project_options
        project_warnings
        CyberBase
        libCyberCraft
        bgfx
        Threads::Threads
        ${SDL2_LIBRARIES})