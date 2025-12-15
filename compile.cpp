#include <iostream>
#include <string>
#include "./RVX_Assembler_v1.2.0/RVX_Assembler.h"
using namespace std;

#define IM "E:/TSRepo/Assembler/im"

int im(string input, string output);
int dex(string input, string output);

int main(int argc, char const *argv[])
{
    RVX_Assembler rvasm;
    cout << "RISC-V ASM Assembler v1.2.0" << endl;
    string input = argv[1];
    string output = argv[2];
    int com = rvasm.replaceLabels(input, output);
    cout << "Generating IM file..." << endl;
    switch (com)
    {
    case 0:
        cout << "RISC-V ASM Compile Success !" << endl;
        break;
    default:
        cout << "ASM ERROR In Line :" << com << endl;
        return -1;
        break;
    }
    // dex(output, IM);
    return 0;
}

int im(string input, string output)
{
    ifstream inputFile;
    inputFile.open(input, ios::in);
    ofstream outputFile;
    outputFile.open(output, ios::out | ios::trunc); //| ios::binary
    if (!(inputFile.is_open() && outputFile.is_open())) return -1;

    int index=1;
    string lineBuf;
    while(getline(inputFile, lineBuf)){
        outputFile<< "im[" << index << "]=32'h" << lineBuf << ";" << '\n';
        index++;
    }

    outputFile.close();
    inputFile.close();
    return 0;
}

int dex(string input, string output)
{
    ifstream inputFile;
    inputFile.open(input, ios::in);
    ofstream outputFile;
    outputFile.open(output, ios::out | ios::trunc); //| ios::binary
    if (!(inputFile.is_open() && outputFile.is_open())) return -1;

    int index=1;
    string lineBuf;
    while(getline(inputFile, lineBuf)){
        uint32_t a=stoul(lineBuf.substr(0,2),nullptr,16);
        uint32_t b=stoul(lineBuf.substr(2,2),nullptr,16);
        uint32_t c=stoul(lineBuf.substr(4,2),nullptr,16);
        uint32_t d=stoul(lineBuf.substr(6,2),nullptr,16);
        outputFile<< d << " " << c << " " << b << " " << a << '\n';
        index++;
    }

    outputFile.close();
    inputFile.close();
    return 0;
}
