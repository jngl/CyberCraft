add_executable(tests
        Test_BimgAdapter.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain LibCyberCraftGraphics)


add_test(AllTest tests)