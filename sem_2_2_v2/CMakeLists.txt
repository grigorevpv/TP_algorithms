cmake_minimum_required(VERSION 3.6)
project(sem_2_2_v2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(sem_2_2_v2 ${SOURCE_FILES})