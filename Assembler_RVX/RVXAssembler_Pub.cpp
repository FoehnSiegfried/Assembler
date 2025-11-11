#ifndef _RVXASSEMBLER_PUB_CPP_
#define _RVXASSEMBLER_PUB_CPP_

#include "RVXAssembler.h"

uint32_t RVXAssembler::Compile(string *inst)
{
    if (!checkInst(inst))
        return 0;
    return instCompileSelect(inst);
}

int RVXAssembler::Compile(string input, string output)
{
    ifstream inputFile;
    inputFile.open(input, ios::in);
    ofstream outputFile;
    outputFile.open(output, ios::out | ios::trunc); //| ios::binary
    if (!(inputFile.is_open() && outputFile.is_open()))
        return OPENERR;

    int index = 1;
    string lineBuf;
    while (getline(inputFile, lineBuf))
    {
        string *inst = instLoad(lineBuf);
        if (!checkInst(inst))
        {
            delete[] inst;
            inputFile.close();
            outputFile.close();
            return index;
        }
        uint32_t instData = instCompileSelect(inst);
        outputFile << hex << setw(8) << setfill('0') << instData << '\n';
        delete[] inst;
        index++;
    }
    outputFile.close();
    inputFile.close();
    return SUCESS;
}

#endif