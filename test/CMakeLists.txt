add_executable(test_log test_log.cc)
target_link_libraries(test_log gtest gtest_main APIS)

add_executable(test_map test_map.cc)
target_link_libraries(test_map gtest gtest_main APIS)
