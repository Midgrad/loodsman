project(loodsman_tests)

add_executable(${PROJECT_NAME} "")

if(NOT TARGET GTest::GTest)
    message("Boost not found by loodsman, let's find one")
    message(${CMAKE_HOST_SYSTEM_NAME})
    include(${CMAKE_SOURCE_DIR}/conan/conan_paths.cmake)
    FIND_PACKAGE(GTest REQUIRED)
endif()

# Internal core sources and headers
file(GLOB SOURCES "./*.h" "./*.hpp" "./*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources ${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} GTest::GTest loodsman)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})



