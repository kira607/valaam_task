cmake_minimum_required(VERSION 3.10)
project(signature)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pthread")

include_directories(src)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)

#add_executable(signature ${SOURCE} ${HEADERS})



