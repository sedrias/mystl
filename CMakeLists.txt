cmake_minimum_required(VERSION 3.28)
project(mystl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MYSTL_ENABLE_ASAN "Enable AddressSanitizer (+UBSan on GCC/Clang)" OFF)
if(MYSTL_ENABLE_ASAN)
    if(MSVC)
        add_compile_options(/fsanitize=address /Zi)
        string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    else()
        add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

add_library(mystl_warnings INTERFACE)
if(MSVC)
    target_compile_options(mystl_warnings INTERFACE /W4 /WX /permissive-)
else()
    target_compile_options(mystl_warnings INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Werror)
endif()

add_library(mystl INTERFACE)
target_include_directories(mystl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(tests)