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
    auto bytes = longlong2bytes(filesize);
    for(auto it = bytes.begin();it != bytes.end();it++) {
        byte temp = *it;
        outputFile.write((const char*)&temp, sizeof(temp));
    }

    inputFile.seekg(0,inputFile.beg);

    // Write the byte and it's frequency to the file.
    for(auto it = char_freq.begin();it != char_freq.end();it++) {
        byte temp = it->first;
        auto bytes = longlong2bytes(it->second);
        outputFile.write((const char*)&temp, sizeof(temp));// Write the byte to file

        // Writing it's frequency.
        for(auto i = bytes.begin();i != bytes.end();i++) {
            byte temp = *i;
            outputFile.write((const char*)&temp, sizeof(temp));
        }
    }


    string code = "";
    // Write the compressed data to the file.
    for (long long i = 0; i < filesize; i++) {
        byte key = inputFile.get();

        code += char_map[key];
        while (code.length() > 8) {
            byte out = 0;
            for(int j = 0;j < 8;j++) {
                out = out<<1;
                if(code[j] == '1') {
                    out = out|0x1;
                }
            }
            outputFile.write((const char*)&out, sizeof(out));
            out = 0;
            code = code.substr(8);
        }
    }
    //处理不满 8 位的 code
    byte out = code.length();
    outputFile.write((const char *)&out, sizeof(out));

    /*
     *     for i in range(len(code)):
        out = out<<1
        if code[i]=='1':
            out = out|1
            */
    out = 0;
    int i;
    for(i = 0;i < code.length();i++) {
        out = out<<1;
        if(code[i] == '1')
            out = out|0x1;
    }
    for(;i<8;i++) {
        out = out<<1;
    }
    outputFile.write((const char*)&out, sizeof(out));
    outputFile.close();
    inputFile.close();

//    // Testing reading binary from file
//    inputFile.open("out.txt",ifstream::binary);
//    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(inputFile), {});
//    for(auto it = buffer.begin();it != buffer.end();it++) {
//        cout<<"it= "<<(int)*it<<std::endl;
//    }
//    inputFile.close();

}

void decompress(string inputFileName,string outputFileName) {

}