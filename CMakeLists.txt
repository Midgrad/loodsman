# CMake version string
cmake_minimum_required(VERSION 3.7.2)
cmake_policy(VERSION 3.4.1)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_HOST_WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0601)
else(CMAKE_HOST_WIN32)
    add_compile_options(-fPIC)
endif(CMAKE_HOST_WIN32)


# Project
project(loodsman VERSION 0.6.1
        DESCRIPTION "Cross-platform udp,tcp and serial connection library"
        HOMEPAGE_URL "https://github.com/Midgrad/loodsman")

# Compile_time configuration
# Presumably, max length of the atomic send/receive in an ordinary network
add_compile_definitions(LOODSMAN_MAX_PACKET_LENGTH=500)

option(LOODSMAN_VERBOSE_OUTPUT "Print loodsman messages to stdout" OFF)

if(NOT DEFINED LOODSMAN_TESTS_ENABLED)
    option(LOODSMAN_TESTS_ENABLED "Enable tests" OFF)
endif(NOT DEFINED LOODSMAN_TESTS_ENABLED)

if(LOODSMAN_TESTS_ENABLED)
    set(LOODSMAN_VERBOSE_OUTPUT ON)
endif(LOODSMAN_TESTS_ENABLED)

if(LOODSMAN_VERBOSE_OUTPUT)
    add_compile_definitions(VERBOSE_OUTPUT)
    message("Enabled loodsman verbose output")
endif(LOODSMAN_VERBOSE_OUTPUT)

add_subdirectory(lib)

# Tests
if(LOODSMAN_TESTS_ENABLED)
    enable_testing()
    add_subdirectory(tests)
endif(LOODSMAN_TESTS_ENABLED)


