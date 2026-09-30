cmake_minimum_required(VERSION 3.28)
project(mystl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MYSTL_ENABLE_ASAN "Enable AddressSanitizer (+UBSan on GCC/Clang)" OFF)
if(MYSTL_ENABLE_ASAN)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

add_library(mystl_warnings INTERFACE)
target_compile_options(mystl_warnings INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Werror)

add_library(mystl INTERFACE)
target_include_directories(mystl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(sandbox)

enable_testing()
add_subdirectory(tests)