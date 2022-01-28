add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC catch project_options project_warnings)

add_executable(tests
        catch_main.cpp
        Test_BimgAdapter.cpp)
target_link_libraries(tests PRIVATE catch_main LibCyberCraftGraphics)


add_test(AllTest tests)