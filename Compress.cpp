//
// Created by Jerry Zhang on 2018/11/29.
//

#include <iostream>
#include "Compress.h"

void compress(string inputFileName,string outFileName) {
    ifstream inputFile(inputFileName,std::ios::binary);
    std::cout<<inputFile.peek();
}
