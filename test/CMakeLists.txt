aux_source_directory(. test_register)
add_executable(tests ${test_register})
target_link_libraries(tests gtest gtest_main APIS)
add_test(
    NAME test_register
    COMMAND test_register
)
