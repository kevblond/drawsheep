cmake_minimum_required(VERSION 2.6)
project(drawsheep)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4 4.4.3 REQUIRED QtGui QtXml)

add_definitions(-std=c++11 -Wall)

include_directories(include ${QT4_INCLUDE_DIR})

set(ALL_LIBRARIES ${QT4_LIBRARY})

file(GLOB SRC_DIRECTORIES "src/*")

add_executable(drawsheep main.cpp ${SRC_DIRECTORIES})

target_link_libraries(drawsheep Qt4::QtGui Qt4::QtXml)