cmake_minimum_required(VERSION 3.12)
project(speck)

set(CMAKE_CXX_STANDARD 14)

file(GLOB src
        "src/*.h"
        "src/*.cpp"
)

add_executable(speck ${src})