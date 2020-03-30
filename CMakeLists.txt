cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-pthread")

set(SOURCE main.cpp Unit.cpp color.cpp Producer.cpp HashGen.cpp Consumer.cpp)
set(HEADERS Producer.h Unit.h test_mode.h color.h HashGen.h Consumer.h FixedQueue.h)

add_executable(untitled ${SOURCE} ${HEADERS})