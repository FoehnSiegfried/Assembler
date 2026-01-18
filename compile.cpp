#include <iostream>
#include <string>
#include <iomanip>
#include "./RVX_Assembler\RVX_Assembler_v3.0.0\RVX_Assembler.h"
using namespace std;

#define IM "E:/TSRepo/Assembler/im"

int im(string input, string output);
int dex(string input, string output);
int real_dex(string input, string output);

int main(int argc, char const *argv[])
{
    RVX_Assembler rvasm;
    cout << "RVX_ASSEMBLER_VERSION : " << RVX_ASSEMBLER_VERSION << endl;
    string input = argv[1];
    string output = argv[2];
    int com = rvasm.compile(input, output);
    switch (com)
    {
    case CONFIRM:
        cout << "RISC-V ASM Compile Success !" << endl;
        break;
    default:
        cout << "ASM ERROR In Line :" << com << endl;
        return -1;
        break;
    }
    // im(output, IM);
    real_dex(output, IM);
    return 0;
}

int im(string input, string output)
{
    ifstream inputFile;
    inputFile.open(input, ios::in);
    ofstream outputFile;
    outputFile.open(output, ios::out | ios::trunc); //| ios::binary
    if (!(inputFile.is_open() && outputFile.is_open())) return -1;

    int index=7;
    string lineBuf;
    while(getline(inputFile, lineBuf)){
        string a=lineBuf.substr(0,2);
        string b=lineBuf.substr(2,2);
        string c=lineBuf.substr(4,2);
        string d=lineBuf.substr(6,2);
        outputFile<< "im[" << index-3 << "]=8'h" << d << ";" << '\n';
        outputFile<< "im[" << index-2 << "]=8'h" << c << ";" << '\n';
        outputFile<< "im[" << index-1 << "]=8'h" << b << ";" << '\n';
        outputFile<< "im[" << index-0 << "]=8'h" << a << ";" << '\n';
        index+=4;
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

int real_dex(string input, string output)
{
    ifstream inputFile;
    inputFile.open(input, ios::in);
    ofstream outputFile;
    outputFile.open(output, ios::out | ios::trunc); //| ios::binary
    if (!(inputFile.is_open() && outputFile.is_open())) return -1;
    stringstream ss;
    int index=1;
    string lineBuf;
    while(getline(inputFile, lineBuf)){
        ss << hex << lineBuf;
        uint32_t inst;
        ss >> inst;
        ss.clear();
        outputFile<< inst << endl;
        index++;
    }

    outputFile.close();
    inputFile.close();
    return 0;
}
