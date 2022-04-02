add_library(bgfx ./src/amalgamated.cpp)

find_package(X11 REQUIRED)

target_include_directories(bgfx PUBLIC include)
target_link_libraries(bgfx
        bx
        bimg
        renderdoc
        khronos
        OpenGL::GL
        OpenGL::GLX
        ${X11_LIBRARIES})

