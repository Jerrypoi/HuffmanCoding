#include <iostream>
#include <vector>
#include <string>
#include "Compress.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    compress("pikachu_testpass.txt","out.cps");
    decompress("out.cps","recover.txt");
    return 0;
}