add_executable(sandbox main.cpp)
target_link_libraries(sandbox PRIVATE mystl)
mystl_copy_asan_runtime(sandbox)
