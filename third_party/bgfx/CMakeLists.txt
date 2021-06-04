add_library(bgfx ./src/amalgamated.cpp)

target_include_directories(bgfx PUBLIC include)
target_link_libraries(bgfx
        bx
        bimg
        renderdoc
        khronos
        OpenGL::GL
        OpenGL::GLX)