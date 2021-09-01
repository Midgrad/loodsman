# Library type
add_library(${PROJECT_NAME} STATIC "")

# Internal core sources and headers
file(GLOB SOURCES "sources/*.h" "sources/*.hpp" "sources/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources)
target_include_directories(${PROJECT_NAME} PUBLIC includes)

if (NOT TARGET Boost_LIBRARIES)
    message("Boost not found by loodsman, let's find one")
    FIND_PACKAGE(Boost REQUIRED)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
endif ()

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
