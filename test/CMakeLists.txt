add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC catch project_options project_warnings)

add_executable(tests tests.cpp
        Test_pointer.cpp
        Test_typeName.cpp
        Test_TypeId.cpp
        Test_id.cpp
        Test_RangeOfNumber.cpp
        Test_math.cpp
        Test_component.cpp)
target_link_libraries(tests PRIVATE catch_main LibCyberCraftCore)


add_test(AllTest tests)