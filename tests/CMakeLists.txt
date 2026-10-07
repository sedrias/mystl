find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}_tests sanity_test.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} ${PROJECT_NAME}_warnings GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
