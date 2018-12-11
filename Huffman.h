//
// Created by Jerry Zhang on 2018/11/22.
//

#ifndef HUFFMANCODING_HUFFMAN_H
#define HUFFMANCODING_HUFFMAN_H

#include <map>
#include <string>
#include <algorithm>
#include <vector>
using std::string;
using std::map;
using std::vector;
using std::sort;
using byte = unsigned char;

class HuffmanNode {
    bool is_leaf;
    HuffmanNode *left_child, *right_child;
    byte value;
    long long weight;
public:
    HuffmanNode(bool is_leaf,byte value = 0, long long weight = 0, HuffmanNode *rigth = nullptr,HuffmanNode *left = nullptr);
    HuffmanNode(HuffmanNode *left,HuffmanNode *right);
    int get_weight() const;
    HuffmanNode *get_left_child() const;
    HuffmanNode *get_right_child() const;
    byte get_value() const ;
    bool isleaf() const;

};


//def traverse_huffman_tree(self, root, code, char_freq):
//"""
//利用递归的方法遍历huffman_tree，并且以此方式得到每个 字符 对应的huffman编码
//        保存在字典 char_freq中
//"""
//if root.isleaf():
//        char_freq[root.get_value()] = code
//        print(("it = %c  and  freq = %d  code = %s")%(chr(root.get_value()),root.get_wieght(), code))
//return None
//else:
//self.traverse_huffman_tree(root.get_left(), code+'0', char_freq)
//self.traverse_huffman_tree(root.get_right(), code+'1', char_freq)

class Huffman {
    HuffmanNode  *root;
public:
    Huffman(bool is_leaf,byte value = 0,long long weight = 0, Huffman *left = nullptr, Huffman *right = nullptr);
    ~Huffman();
    HuffmanNode *get_root();
    long long get_weight();
    void traverse_tree(HuffmanNode *root,string code,map<byte,string> &char_map);
    static Huffman *build_tree(vector<Huffman*> &tree_list);

};


#endif //HUFFMANCODING_HUFFMAN_H
