find_package(GTest CONFIG REQUIRED)

add_executable(mystl_tests
    sanity_test.cpp
)
target_link_libraries(mystl_tests PRIVATE mystl mystl_warnings GTest::gtest_main)

if(MSVC AND MYSTL_ENABLE_ASAN)
    get_filename_component(MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    add_custom_command(TARGET mystl_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
            "$<TARGET_FILE_DIR:mystl_tests>"
    )
endif()

include(GoogleTest)
gtest_discover_tests(mystl_tests)