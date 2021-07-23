# CMake version string
cmake_minimum_required(VERSION 3.7.2)
cmake_policy(VERSION 3.4.1)

# Project
set(PROJECT_NAME "loodsman")
project(${PROJECT_NAME})

# Versions
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

# Includes
#include()

# Library type
add_library(${PROJECT_NAME} STATIC "")

# Internal core sources and headers
file(GLOB SOURCES "sources/*.h" "sources/*.hpp" "sources/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC includes )

#target_link_libraries(${PROJECT_NAME} )

#add_subdirectory()