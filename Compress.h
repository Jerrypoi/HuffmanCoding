//
// Created by Jerry Zhang on 2018/11/29.
//

#ifndef HUFFMANCODING_COMPRESS_H
#define HUFFMANCODING_COMPRESS_H

#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include "Huffman.h"
using std::ofstream;
using std::ifstream;
using std::string;
void compress(string inputFileName,string outFileName);
void decompress(string inputFileName,string outputFileName);
vector<byte> longlong2bytes(long long paramInt);

#endif //HUFFMANCODING_COMPRESS_H
