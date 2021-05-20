add_library(bx ./src/amalgamated.cpp)
target_include_directories(bx PUBLIC include)
target_link_libraries(bx ini)