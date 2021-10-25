# CMake version string
cmake_minimum_required(VERSION 3.7.2)
cmake_policy(VERSION 3.4.1)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

add_compile_options(-fPIC)

# Project
project(loodsman VERSION 0.5.1
        DESCRIPTION "Cross-platform udp,tcp and serial connection library"
        HOMEPAGE_URL "https://github.com/Midgrad/loodsman")

# Compile_time configuration
# Presumably, max length of the atomic send/receive in an ordinary network
add_compile_definitions(MAX_PACKET_LENGTH=500 MAX_MTU=1500 DEBUG_VERBOSITY=1)

add_subdirectory(lib)


if(NOT DEFINED TESTS_ENABLED)
    option(TESTS_ENABLED "Enable tests" ON)
endif(NOT DEFINED TESTS_ENABLED)

# Tests
if(TESTS_ENABLED)
    enable_testing()
    add_subdirectory(tests)
endif(TESTS_ENABLED)

