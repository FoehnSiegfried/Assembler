#ifndef _RVX_ASSEMBLER_PUB_CPP_
#define _RVX_ASSEMBLER_PUB_CPP_

#include "RVX_Assembler.h"

RVX_Assembler::RVX_Assembler(const string &cache)
{
    this->cache = cache;
}
RVX_Assembler::~RVX_Assembler()
{
}

uint32_t RVX_Assembler::lineCompile(const string &line)
{
    string *inst = splitLine(line);
    uint32_t machineCode = RV32I(inst);
    delete[] inst;
    return machineCode;
}
int RVX_Assembler::fileCompile(const string &inputFile, const string &outputFile)
{
    preprocessing(inputFile, cache + "pre");
    int verifyResult = verify(cache + "pre_label");
    if (verifyResult != SUCCESS)
    {
        return verifyResult; // error line number
    }

    ifstream inputStream;
    ofstream outputStream;
    inputStream.open(cache + "pre_label", ios::in);
    if (!inputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }
    outputStream.open(outputFile, ios::out | ios::trunc | ios::binary);
    if (!outputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }

    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        uint32_t machineCode = lineCompile(lineBuf);
        outputStream.write(reinterpret_cast<const char*>(&machineCode), sizeof(machineCode));
    }

    inputStream.close();
    outputStream.close();
    return SUCCESS;
}

int RVX_Assembler::fileCompile_Word(const string &inputFile, const string &outputFile)
{
    preprocessing(inputFile, cache + "pre");
    int verifyResult = verify(cache + "pre_label");
    if (verifyResult != SUCCESS)
    {
        return verifyResult; // error line number
    }

    ifstream inputStream;
    ofstream outputStream;
    inputStream.open(cache + "pre_label", ios::in);
    if (!inputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }
    outputStream.open(outputFile, ios::out | ios::trunc | ios::binary);
    if (!outputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }

    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        uint32_t machineCode = lineCompile(lineBuf);
        outputStream << hex << setw(8) << setfill('0') << machineCode << '\n';
    }

    inputStream.close();
    outputStream.close();
    return SUCCESS;
}

int RVX_Assembler::verify(const string &inputFile)
{
    ifstream inputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }

    string lineBuf;
    int lineNum = 1;
    while (getline(inputStream, lineBuf))
    {
        string *vals = splitLine(lineBuf);
        if (!verifyLine(vals))
        {
            inputStream.close();
            return lineNum; // error line number
        }
        lineNum++;
        delete[] vals;
    }
    inputStream.close();
    return SUCCESS;
}
int RVX_Assembler::preprocessing(const string &inputFile, const string &outputFile)
{
    // 去除注释和多余空格
    ifstream inputStream;
    ofstream outputStream;

    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }
    outputStream.open(outputFile, ios::out | ios::trunc); //| ios::binary
    if (!outputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }

    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        string procLine;
        for (int i = 0; i < lineBuf.length(); i++)
        {
            if (lineBuf[i] == '#') // 注释
                break;
            if (lineBuf[i] == ' ' && lineBuf[i - 1] == ' ') // 多余空格
                continue;
            procLine += lineBuf[i];
        }
        outputStream << procLine << endl;
    }

    inputStream.close();
    outputStream.close();

    preprocessLabel(outputFile, cache+"pre_label"); // 预处理标签
    
    return SUCCESS;
}

#endif // _RVX_ASSEMBLER_PUB_CPP_