//
// Created by Jerry Zhang on 2018/11/22.
//

#include "Huffman.h"
HuffmanNode::HuffmanNode(bool is_leaf, byte value, long long int weight, HuffmanNode *right,HuffmanNode *left) {
    this->is_leaf = is_leaf;
    this->value = value;
    this->weight = weight;
    this->right_child = right;
    this->left_child = left;
}
HuffmanNode::HuffmanNode(HuffmanNode *left, HuffmanNode *right) {
    this->left_child = left;
    this->right_child = right;
    is_leaf = false;
    weight = left->get_weight() + right->get_weight();

}
int HuffmanNode::get_weight() const {
    return weight;
}
byte HuffmanNode::get_value() const {
    return value;
}
HuffmanNode *HuffmanNode::get_left_child() const {
    return left_child;
}
HuffmanNode *HuffmanNode::get_right_child() const{
    return right_child;
}
bool HuffmanNode::isleaf() const {
    return is_leaf;
}

Huffman::Huffman(bool is_leaf, byte value, long long int weight, Huffman *left, Huffman *right) {
    if(is_leaf) {
        root = new HuffmanNode(true,value,weight);
    } else {
        root = new HuffmanNode(left->get_root(),right->get_root());
    }
}

Huffman::~Huffman() {
    delete root;
}
long long Huffman::get_weight() {
    return root->get_weight();
}
HuffmanNode *Huffman::get_root() {
    return root;
}
void Huffman::traverse_tree(HuffmanNode *root, string code, map<byte, string> &char_map) {
    if( root->isleaf() ) {
        char_map.insert(std::pair<byte,string> (root->get_value(),code));
    } else {
        traverse_tree(root->get_left_child(),code + "0",char_map);
        traverse_tree(root->get_right_child(),code + "1",char_map);
        // TODO: Low efficiency here.
    }
}
Huffman *Huffman::build_tree(vector<Huffman*> &tree_list) {
    while(tree_list.size() > 1) {
        sort(tree_list.begin(),tree_list.end(),[](Huffman *a, Huffman *b){return a->get_weight() > b->get_weight();});
        Huffman *tree1 = tree_list.back();
        tree_list.pop_back();
        Huffman *tree2 = tree_list.back();
        tree_list.pop_back();
        Huffman *newTree = new Huffman(false,0,0,tree1,tree2);
        tree_list.push_back(newTree);
    }
    return tree_list.front();
}
