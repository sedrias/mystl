find_package(GTest CONFIG REQUIRED)

add_executable(mystl_tests
    sanity_test.cpp
)
target_link_libraries(mystl_tests PRIVATE mystl mystl_warnings GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(mystl_tests)
