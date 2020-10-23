add_library(Glad
        src/glad.cpp
        include/glad/glad.h)

target_include_directories(Glad PUBLIC include)
target_link_libraries(Glad ${SDL2_LIBRARY})
