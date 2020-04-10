cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-pthread")

file(GLOB SOURCE *.cpp)
file(GLOB HEADERS *.h)

add_executable(untitled ${SOURCE} ${HEADERS})