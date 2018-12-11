#include <iostream>
#include <vector>
#include <string>
#include "Compress.h"
using namespace std;
int main(int argc,char *args[]) {
    cout<<"argc = "<<argc<<endl;
    cout<<"args[0] = " <<args[0]<<endl;
    if(argc == 1) {
        compress("pikachu_testpass.txt","out.cps");
        decompress("out.cps","recover.txt");
        return 0;
    }
    else if(argc != 4) {
        return -1;
    }
    if(string(args[1]) == "-c") {
        compress(args[2],args[3]);
    } else if(string(args[1]) == "-d") {
        decompress(args[2],args[3]);
    }
    return 0;
}