# Library type
add_library(${PROJECT_NAME} STATIC "")

# Internal core sources and headers
file(GLOB SOURCES "sources/*.h" "sources/*.hpp" "sources/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources)
target_include_directories(${PROJECT_NAME} PUBLIC includes )

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})