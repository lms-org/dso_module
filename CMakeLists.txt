cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
    "src/dsodometry.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/dsodometry.h"
)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wreturn-type -Wpedantic ")

add_subdirectory(dso)

include_directories(include)
add_library(dsodometry MODULE ${SOURCES} ${HEADERS})
target_link_libraries(dsodometry PRIVATE ${CONAN_LIBS})
