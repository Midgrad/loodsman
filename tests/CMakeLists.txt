project(loodsman_tests)

add_executable(${PROJECT_NAME} "")

#TODO: add checking of the exising gtest and dynamically download it otherwise

# Internal core sources and headers
file(GLOB SOURCES "./*.h" "./*.hpp" "./*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources ${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} loodsman gtest_main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})



