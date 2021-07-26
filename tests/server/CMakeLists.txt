set(EXE_NAME "test_server")

# Library type
add_executable(${EXE_NAME} main.cpp)

# Internal core sources and headers
file(GLOB SOURCES "sources/*.h" "sources/*.hpp" "sources/*.cpp" "*.cpp" "*.h")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC includes )

target_link_libraries(${EXE_NAME} ${PROJECT_NAME})
