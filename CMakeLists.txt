cmake_minimum_required(VERSION 3.14)

project(pnmstream VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(pnmstream)

target_include_directories(pnmstream
PUBLIC
    include
)

add_subdirectory(src)

add_subdirectory(examples)

option(PNMSTREAM_BUILD_TESTS "Build unit tests" ON)
if(PNMSTREAM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
