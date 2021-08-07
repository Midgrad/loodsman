project(loodsman_tests)

find_package(GTest REQUIRED)
# In Ubuntu install libgtest-dev, not googletest

add_executable(${PROJECT_NAME} "")

# Internal core sources and headers
file(GLOB SOURCES "./*.h" "./*.hpp" "./*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources ${GTEST_INCLUDE_DIRS})

# GTest::GTest and GTest::Main  is removed in cmake 3.30 and repalced with GTest::gtest GTest::gtest_main
target_link_libraries(${PROJECT_NAME} libloodsman GTest::Main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# Googletest recommendation from https://github.com/google/googletest/blob/master/googletest/README.md#as-a-shared-library-dll
target_compile_definitions(${PROJECT_NAME} PRIVATE GTEST_LINKED_AS_SHARED_LIBRARY=1)


