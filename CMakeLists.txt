cmake_minimum_required(VERSION 3.14)

project(pnmstream VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(pnmstream
    src/stream/PPMStream.cpp
    src/stream/buffer/PPMBuffer.cpp
    src/stream/PNMDrawer.cpp
)

target_include_directories(pnmstream
PUBLIC
    include
)
