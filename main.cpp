#include <iostream>
#include "Compress.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;

    compress("test.txt","out.txt");
    return 0;
}