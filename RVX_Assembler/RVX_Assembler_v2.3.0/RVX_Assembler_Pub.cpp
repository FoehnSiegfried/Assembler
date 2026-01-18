#ifndef _RVX_ASSEMBLER_PUB_CPP_
#define _RVX_ASSEMBLER_PUB_CPP_

#include "RVX_Assembler.h"

#define RVX_ASSEMBLER_PUB_VERSION "2.3.0"

int RVX_Assembler::getCodeNum()
{
    return asminst.getCodeNum();
}

uint32_t RVX_Assembler::getCode(int codeIndex)
{
    return asminst.getCode(codeIndex);
}

int RVX_Assembler::interpret(const string &line)
{
    loadInst(line);
    return asminst.interpret(inst);
}

int RVX_Assembler::compile(const string &inputFile, const string &outputFile)
{
    int verifyInfo = verify(inputFile);
    if (verifyInfo != CONFIRM)
    {
        return verifyInfo;
    }
    int collInfo = collectLabels(inputFile);
    if (collInfo != CONFIRM)
    {
        return collInfo;
    }

    ifstream inputStream;
    ofstream outputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");
#ifdef RVX_TEST_OUTPUT_HEX
    outputStream.open(outputFile, ios::out | ios::trunc); // | ios::binary
#else
    outputStream.open(outputFile, ios::out | ios::trunc | ios::binary);
#endif
    if (!outputStream.is_open())
        throw runtime_error("File can't be opened.");

    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (inst[0] == RVX_INST_LABEL)
            continue;
        if (loadLabels(index) != CONFIRM)
            return index;
        if (asminst.interpret(inst) != CONFIRM)
            return index;
        for (int i = 0; i < asminst.getCodeNum(); i++)
        {
#ifdef RVX_TEST_OUTPUT_HEX
            outputStream << hex << setw(8) << setfill('0') << asminst.getCode(i) << '\n';
#else
            outputStream << asminst.getCode(i);
#endif
        }
        index++;
    }
    outputStream.close();
    inputStream.close();
    return CONFIRM;
}

int RVX_Assembler::replaceLabels(const string &inputFile, const string &outputFile, bool removeLabels)
{
    int verifyInfo = verify(inputFile);
    if (verifyInfo != CONFIRM)
    {
        return verifyInfo;
    }
    int collInfo = collectLabels(inputFile);
    if (collInfo != CONFIRM)
    {
        return collInfo;
    }

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
        if (inst[0] == RVX_INST_LABEL)
        {
            if (!removeLabels)
                outputStream << inst[0] << " " << inst[1] << '\n';
            continue;
        }
        if (loadLabels(index) != CONFIRM)
            return index;
        outputStream << inst[0];
        for (int i = 1; ((i < RVX_MAX_INSTVOLUNM) && (inst[i] != PLACEHOLDER_STRING)); i++)
        {
            outputStream << " " << inst[i];
        }
        outputStream << '\n';
        index++;
    }
    outputStream.close();
    inputStream.close();
    return CONFIRM;
}

int RVX_Assembler::verify(const string &inputFile)
{
    int collInfo = collectLabels(inputFile);
    if (collInfo != CONFIRM)
    {
        return collInfo;
    }
    ifstream inputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");

    int index = 1;
    int lineNum = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (inst[0] == RVX_INST_LABEL)
            continue;
        loadLabels(index);
        if (verifyInst() != CONFIRM)
        {
            inputStream.close();
            return lineNum;
        }
        lineNum++;
        index++;
    }

    inputStream.close();
    return CONFIRM;
}

#endif // _RVX_ASSEMBLER_PUB_CPP_