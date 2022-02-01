# Library type
add_library(${PROJECT_NAME} STATIC "")

# Internal core sources and headers
file(GLOB SOURCES "sources/*.h" "sources/*.hpp" "sources/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE sources)
target_include_directories(${PROJECT_NAME} PUBLIC includes)

if(NOT TARGET Boost::Boost)
    message("Boost not found by loodsman, let's find one")
    # Disabled to allow cmake find boost from the system
    set(Boost_NO_SYSTEM_PATHS OFF)
    # Enabled to allow to use from boost_root
    set(Boost_NO_BOOST_CMAKE ON)
    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/deps/boost/")
    message("${BOOST_ROOT}")
    FIND_PACKAGE(Boost REQUIRED)
endif()

target_link_libraries(${PROJECT_NAME} Boost::headers)
