if(USE_CONAN)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
endif(USE_CONAN)

set(SOURCES
    "src/dsodometry.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/dsodometry.h"
    "include/MyIOWrapper.h"
)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wreturn-type -Wpedantic ")

include_directories(include)
add_library(dsodometry MODULE ${SOURCES} ${HEADERS})
if(USE_CONAN)
target_link_libraries(dsodometry PRIVATE ${CONAN_LIBS})
else()
target_link_libraries(dsodometry PRIVATE lmscore lms_imaging dso)
endif(USE_CONAN)
