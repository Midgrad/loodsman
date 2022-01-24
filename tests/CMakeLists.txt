project(loodsman_tests)

add_executable(${PROJECT_NAME} "")

# Internal core sources and headers
file(GLOB SOURCES "./*.h" "./*.hpp" "./*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

if(TARGET gtest) # Temporary solution to link gtest-submodule
    message("loodsman: gtest is defined already, trying to link")
    target_link_libraries(${PROJECT_NAME} gtest loodsman)
elseif(NOT TARGET GTest::GTest) # Assuming standalone build
    message("GTest not found by loodsman, let's find one")
    set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/deps/gtest")
    FIND_PACKAGE(GTest REQUIRED)
    target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main loodsman)
endif()


#target_include_directories(${PROJECT_NAME} PRIVATE sources ${GTEST_INCLUDE_DIRS})


add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})



