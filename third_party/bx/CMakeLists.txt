add_library(bx ./src/amalgamated.cpp)
target_include_directories(bx PUBLIC include)
target_link_libraries(bx ini ${CMAKE_DL_LIBS})
#add_compile_definitions(bx __linux__)