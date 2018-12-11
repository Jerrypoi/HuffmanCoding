#include <iostream>
#include <vector>
#include <string>
#include "Compress.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    string test = "01234567,";
    compress("test.txt","out.txt");
    return 0;
}