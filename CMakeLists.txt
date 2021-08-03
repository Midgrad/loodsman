# CMake version string
cmake_minimum_required(VERSION 3.7.2)
cmake_policy(VERSION 3.4.1)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# add_compile_options(-Wall -fPIC -O1)

# Project
project(loodsman VERSION 0.3.1
        DESCRIPTION "Cross-platform udp,tcp and serial connection library"
        HOMEPAGE_URL "https://github.com/Midgrad/loodsman")

if (NOT DEFINED Boost_LIBRARIES)
    FIND_PACKAGE(Boost REQUIRED)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
endif()

# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

add_subdirectory(lib)

option(TESTS_ENABLED "Enable tests" ON)

# Tests
if(TESTS_ENABLED)
    add_subdirectory(tests)
endif(TESTS_ENABLED)
