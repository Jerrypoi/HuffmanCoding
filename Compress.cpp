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
    cout<<"Compressing last code len = " <<code.length()<<std::endl;
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
    ifstream inputFile(inputFileName,ifstream::binary);
    std::vector<unsigned char> data(std::istreambuf_iterator<char>(inputFile), {});
    long long filesize = 0;
    int i;
    for(i = 0;i < sizeof(long long);i++) {
        filesize = filesize<<8; // TODO: determine 8 or 1
        filesize = filesize | data[i];
    }
    cout<<"Got filesize = "<<filesize<<std::endl;
    long long count = 0;
    map<byte,long long> char_freq;
    while(count < filesize) {
        byte temp = data[i];
        long long freq = 0;
        i++;
        for(int j = 0;j < sizeof(long long);j++,i++) {
            freq = freq << 8;
            freq = freq | data[i];
        }
        char_freq.insert(std::pair<byte,long long>(temp,freq));
        count += freq;
    }
    // This test is passed zo~
    std::cout<<"decompress freq map:"<<std::endl;
    for (auto it = char_freq.begin(); it != char_freq.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    // Build Huffman tree
    vector<Huffman *> tree_list;
    for(auto it = char_freq.begin();it != char_freq.end();it++) {
        Huffman *tree = new Huffman(true,it->first,it->second);
        tree_list.push_back(tree);
    }
    Huffman *tree = Huffman::build_tree(tree_list);
    ofstream outputFile(outputFileName,ofstream::binary);
    map<byte, string> char_map;
    tree->traverse_tree(tree->get_root(), "", char_map);
    HuffmanNode *node = tree->get_root();
    // TODO: 反向建立 map？ 即，<string,byte> 型？
    string code = "";
    for(;i < data.size();i++) {
        byte temp = data[i];
        int j = 0;
        for(j = 0;j < 8;j++) {
            if((temp & 128) == 128) {
                code += "1";
            } else {
                code += "0";
            };
            temp <<= 1;
        }
        while(code.length() > 255) {
            if(node->isleaf()) {
                byte temp = node->get_value();
                outputFile.write((const char*)&temp, sizeof(temp));
                node = tree->get_root();
            }
            if(code[0] == '1') {
                node = node->get_right_child();
            } else {
                node = node->get_left_child();
            }
            code = code.substr(1);
        }
    }
    cout<<"code size: "<<code.length()<<std::endl;
    // First byte: the remaining bits length
    while(code.size() > 16){
        if(node->isleaf()) {
            byte temp = node->get_value();
            outputFile.write((const char*)&temp, sizeof(temp));
            node = tree->get_root();
        }
        if(code[0] == '1') {
            node = node->get_right_child();
        } else {
            node = node->get_left_child();
        }
        code = code.substr(1);
    }


//    HuffmanNode *node = tree->get_root();
//    for(int i = 0;i < f)

    string sub_code = code.substr(code.length()-16,8);


    int last_len = 0;
    for(int j = 0;j < 8;j++) {
        last_len <<= 1;
        if(sub_code[j] == '1' ) {
            last_len = last_len | 1;
        }
    }
    cout<<"subcode = "<<sub_code<<std::endl;
    cout<<"last len = "<<last_len<<std::endl;
    cout<<"current code = "<<code<<std::endl;
    code = code.substr(0,code.length() - 16) + code.substr(code.length() - 8,last_len);
    cout<<"last_code = "<<code<<std::endl;
    while(code.length() > 0) {
        if(node->isleaf()) {
            byte temp = node->get_value();
            outputFile.write((const char *)&temp, sizeof(temp));
            node = tree->get_root();
        }
        if(code[0] == '1') {
            node = node->get_right_child();
        }
        else {
            node = node->get_left_child();
        }
        code = code.substr(1);
    }
    if(node->isleaf()) {
        byte temp = node->get_value();
        outputFile.write((const char *)&temp, sizeof(temp));
        node = tree->get_root();
    }

    outputFile.close();
    inputFile.close();
}