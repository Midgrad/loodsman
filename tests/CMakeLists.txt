project(loodsman_tests)

#find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

# Internal core sources and headers
file(GLOB SOURCES "./*.h" "./*.hpp" "./*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources ${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} libloodsman CONAN_PKG::gtest)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})




