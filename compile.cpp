#include <iostream>
#include <string>
#include "./Assembler_RVX/RVXAssembler.h"

#define IM "E:/TSRepo/Assembler/im"

int im(string input, string output);
int dex(string input, string output);

int main(int argc, char const *argv[])
{
    RVXAssembler rvasm;
    string input = argv[1];
    string output = argv[2];
    int com = rvasm.Compile(input, output);
    switch (com)
    {
    case SUCESS:
        cout << "RISC-V ASM Compile Sucess !" << endl;
        break;
    case OPENERR:
        cout << "FILE OPEN ERROR" << endl;
        return -1;
        break;
    default:
        cout << "ASM ERROR In Line :" << com << endl;
        return -1;
        break;
    }
    dex(output, IM);
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
