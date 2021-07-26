
# Includes
#include()

# Library type
add_executable("test" main.cpp)

# Internal core sources and headers
file(GLOB SOURCES "sources/*.h" "sources/*.hpp" "sources/*.cpp" "*.cpp" "*.h")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC includes )

target_link_libraries("test" ${PROJECT_NAME})
