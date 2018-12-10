//
// Created by Jerry Zhang on 2018/11/29.
//


#include "Compress.h"
using std::cout;
using std::cerr;
vector<byte> longlong2bytes(long long paramInt) {
    vector<unsigned char> arrayOfByte(sizeof(long long));
    for (int i = 0; i < sizeof(long long); i++)
        arrayOfByte[sizeof(long long) - 1 - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}

void compress(string inputFileName,string outFileName) {
    ifstream inputFile(inputFileName,std::ifstream::binary);
    // TODO: do something if failing in file opening.
    cout<<"OK here"<<std::endl;
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
//     Printing out the whole frequency list.
    for (auto it = char_freq.begin(); it != char_freq.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    vector<Huffman *> tree_list;
    for(auto it = char_freq.begin();it != char_freq.end();it++) {
        Huffman *tree = new Huffman(true,it->first,it->second);
        tree_list.push_back(tree);
    }

    Huffman *tree = Huffman::build_tree(tree_list);
    map<byte, string> char_map;
    tree->traverse_tree(tree->get_root(), "", char_map);

    // Print out the char_map for testing.
    for (auto it = char_map.begin(); it != char_map.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    ofstream outputFile(outFileName,std::ofstream::binary);
    // TODO: do something if failing in opening file.
    outputFile.write((const char*)&filesize, sizeof(filesize));
    cout<<filesize<<std::endl;
    inputFile.seekg(0,inputFile.beg);

    for(auto i = char_freq.begin();i != char_freq.end();i++) {

    }

    string code = "";
    // Write the compressed data to the file.
    for (long long i = 0; i < filesize; i++) {
        byte key = inputFile.get();
        code = code + char_map[key];
        while (code.length() > 8) {
//            std::cout << "Find" << std::endl;
            break;
        }
    }


    outputFile.close();
    inputFile.close();
    inputFile.open("out.txt",ifstream::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(inputFile), {});
    for(auto it = buffer.begin();it != buffer.end();it++) {
        cout<<"it= "<<(int)*it<<std::endl;
    }
}
