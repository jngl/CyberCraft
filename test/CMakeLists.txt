add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC catch)
target_link_libraries(catch_main PRIVATE project_options)

add_executable(tests tests.cpp Test_BTreePlus.cpp)
target_link_libraries(tests PRIVATE project_warnings project_options catch_main LibCyberCraftCore)


add_test(AllTest tests)