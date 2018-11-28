cmake_minimum_required(VERSION 3.12)
project(HuffmanCoding)

set(CMAKE_CXX_STANDARD 14)

add_executable(HuffmanCoding main.cpp Huffman.cpp Huffman.h Compress.cpp Compress.h)