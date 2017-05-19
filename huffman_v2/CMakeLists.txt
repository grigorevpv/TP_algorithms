cmake_minimum_required(VERSION 3.7)
project(huffman_v2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Huffman.h)
add_executable(huffman_v2 ${SOURCE_FILES})