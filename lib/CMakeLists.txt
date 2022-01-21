# Library type
add_library(${PROJECT_NAME} STATIC "")

# Internal core sources and headers
file(GLOB SOURCES "sources/*.h" "sources/*.hpp" "sources/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources)
target_include_directories(${PROJECT_NAME} PUBLIC includes)

if (NOT TARGET Boost_LIBRARIES)
    message("Boost not found by loodsman, let's find one")
    message(${CMAKE_HOST_SYSTEM_NAME})
    if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
        FIND_PACKAGE(Boost COMPONENTS system REQUIRED)
    elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        FIND_PACKAGE(Boost REQUIRED)
    endif ()
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
endif ()

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} pthread)
