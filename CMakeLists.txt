cmake_minimum_required(VERSION 3.6)
project(drawsheep)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SRC_DIRECTORIES "src/*")

add_executable(drawsheep main.cpp ${SRC_DIRECTORIES})