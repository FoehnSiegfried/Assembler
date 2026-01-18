#ifndef _RVX_ASSEMBLER_PUB_CPP_
#define _RVX_ASSEMBLER_PUB_CPP_

#include "RVX_Assembler.h"

RVX_Assembler::RVX_Assembler()
{
    labels = new HashTable<string, int>(101, true);
}
RVX_Assembler::~RVX_Assembler()
{
    inst[0] = "";
    inst[1] = "";
    inst[2] = "";
    inst[3] = "";
    labels->~HashTable<string, int>();
    cout << "RVX Assembler Destroyed." << endl;
    // delete labels;
}
uint32_t RVX_Assembler::interpret(const string &line)
{
    loadInst(line);
    return RV32I();
}
int RVX_Assembler::compile(const string &inputFile, const string &outputFile)
{
    int verifyInfo = verify(inputFile);
    if (verifyInfo != 0)
    {
        return verifyInfo; // error line number
    }
    collectLabels(inputFile);

    ifstream inputStream;
    ofstream outputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");
    outputStream.open(outputFile, ios::out | ios::trunc); // | ios::binary
    if (!outputStream.is_open())
        throw runtime_error("File can't be opened.");

    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (inst[0] == TAG_LABEL)
        {
            continue;
        }
        loadLabels(index);
        uint32_t machineCode = RV32I();
        outputStream << hex << setw(8) << setfill('0') << machineCode << '\n';
        index++;
    }
    outputStream.close();
    inputStream.close();
    return 0;
}
int RVX_Assembler::replaceLabels(const string &inputFile, const string &outputFile, bool removeLabels)
{
    int verifyInfo = verify(inputFile);
    if (verifyInfo != 0)
    {
        return verifyInfo; // error line number
    }
    collectLabels(inputFile);

    ifstream inputStream;
    ofstream outputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");
    outputStream.open(outputFile, ios::out | ios::trunc); // | ios::binary
    if (!outputStream.is_open())
        throw runtime_error("File can't be opened.");

    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (inst[0] == TAG_LABEL)
        {
            if (!removeLabels)
                outputStream << inst[0] << " " << inst[1] << '\n';
            continue;
        }
        loadLabels(index);
        outputStream << inst[0];
        if (inst[1] != "")
            outputStream << " " << inst[1];
        if (inst[2] != "")
            outputStream << " " << inst[2];
        if (inst[3] != "")
            outputStream << " " << inst[3];
        outputStream << '\n';
        index++;
    }
    outputStream.close();
    inputStream.close();
    return 0;
}
int RVX_Assembler::verify(const string &inputFile)
{
    int clInfo = collectLabels(inputFile);
    if (clInfo != 0)
        return clInfo;

    ifstream inputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");

    int lineNum = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (!verifyInst())
        {
            inputStream.close();
            return lineNum;
        }
        lineNum++;
    }

    inputStream.close();
    return 0;
}

#endif // _RVX_ASSEMBLER_PUB_CPP_