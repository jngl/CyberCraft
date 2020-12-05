add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC catch)

add_executable(tests tests.cpp
        Test_BTreePlus.cpp
        Test_pointer.cpp
        Test_typeName.cpp
        Test_TypeId.cpp)
target_link_libraries(tests PRIVATE project_warnings project_options catch_main LibCyberCraftCore)


add_test(AllTest tests)