# CMake version string
cmake_minimum_required(VERSION 3.7.2)
cmake_policy(VERSION 3.4.1)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# add_compile_options(-Wall -fPIC -O1)

# Project
set(PROJECT_NAME "loodsman")
project(${PROJECT_NAME})

# Versions
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)

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
