project(loodsman_tests)

add_executable(${PROJECT_NAME} "")

# Checking of the exising gtest and dynamically download it otherwise
if (NOT TARGET gtest)
    message("Gtest not found by loodsman, fetching from internet")
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

    FetchContent_MakeAvailable(googletest)
endif ()

# Internal core sources and headers
file(GLOB SOURCES "./*.h" "./*.hpp" "./*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources ${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} gtest_main loodsman)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})



