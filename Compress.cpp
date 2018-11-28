//
// Created by Jerry Zhang on 2018/11/29.
//


#include "Compress.h"
vector<byte> longlong2bytes(long long paramInt) {
    vector<unsigned char> arrayOfByte(sizeof(long long));
    for (int i = 0; i < sizeof(long long); i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}

void compress(string inputFileName,string outFileName) {
    ifstream inputFile(inputFileName,std::ifstream::binary);
    // TODO: do something if failing in file opening.

    // Find file size;
    long long filesize = 0;
    inputFile.seekg(0,inputFile.end);
    filesize = inputFile.tellg();
    inputFile.seekg(0,inputFile.beg);


    map<byte,long long> char_freq;
    for(int i = 0;i < filesize;i++) {
        byte byte1 = inputFile.get();
        if(char_freq.find(byte1) != char_freq.end()) {
            char_freq.at(byte1)++;
        } else {
            char_freq.insert(std::pair<byte,long long>(byte1,1));
        }
    }
    // Printing out the whole frequency list.
//    for(auto it = char_freq.begin();it != char_freq.end();it++) {
//        std::cout<<it->first<<" "<<it->second<<std::endl;
//    }
    vector<Huffman *> tree_list;
    for(auto it = char_freq.begin();it != char_freq.end();it++) {
        Huffman *tree = new Huffman(true,it->first,it->second);
        tree_list.push_back(tree);
    }
    ofstream outputFile(outFileName,std::ofstream::binary);
    // TODO: do something if failing in opening file.

    auto bytes = longlong2bytes(filesize);
    for(auto it = bytes.begin();it != bytes.end();it++) {

    }

}
