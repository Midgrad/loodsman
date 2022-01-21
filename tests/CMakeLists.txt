project(loodsman_tests)

add_executable(${PROJECT_NAME} "")

# Internal core sources and headers
file(GLOB SOURCES "./*.h" "./*.hpp" "./*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

if(NOT TARGET GTest::GTest)
    message("GTest not found by loodsman, let's find one")
    set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/deps/gtest")
    FIND_PACKAGE(GTest REQUIRED)
endif()


#target_include_directories(${PROJECT_NAME} PRIVATE sources ${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main loodsman)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})



