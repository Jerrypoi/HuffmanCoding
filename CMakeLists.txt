cmake_minimum_required(VERSION 3.9)
project(HuffmanCoding)

set(CMAKE_CXX_STANDARD 14)

add_executable(HuffmanCoding main.cpp Huffman.cpp Huffman.h Compress.cpp Compress.h)