#ifndef _RVX_ASSEMBLER_PUB_CPP_
#define _RVX_ASSEMBLER_PUB_CPP_

#include "RVX_Assembler.h"

#define RVX_ASSEMBLER_PUB_VERSION "2.1.0"

int RVX_Assembler::getAsminstNum()
{
    return asminst.getAsminstNum();
}

uint32_t RVX_Assembler::getAsminst(int asminstIndex)
{
    return asminst.getAsminst(asminstIndex);
}

int RVX_Assembler::interpret(const string &line)
{
    loadInst(line);
    return asminst.RVX_Asm(curinst);
}

int RVX_Assembler::replaceLabels(const string &inputFile, const string &outputFile, bool removeLabels = true)
{
    int verifyInfo = verify(inputFile);
    if (verifyInfo != CONFIRM)
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
        if (curinst[0] == RVXINST_LABEL)
        {
            if (!removeLabels)
                outputStream << curinst[0] << " " << curinst[1] << '\n';
            continue;
        }
        loadLabels();
        outputStream << curinst[0];
        if (curinst[1] != "")
            outputStream << " " << curinst[1];
        if (curinst[2] != "")
            outputStream << " " << curinst[2];
        if (curinst[3] != "")
            outputStream << " " << curinst[3];
        outputStream << '\n';
        index++;
    }
    outputStream.close();
    inputStream.close();
    return 0;
}

int RVX_Asminst::findKey(string &key)
{
    bool inReg = regMap.find(key);
    bool inRVX = RVXinstMap.find(key);
    bool inAsm = AsminstMap.find(key);

    bool inRV32I = RV32IMap.find(key);

    if (inReg || inRVX || inAsm || inRV32I)
    {
        return CONFIRM;
    }
    else
    {
        return NEGATION;
    }
}

int RVX_Assembler::verify(const string &inputFile)
{
    int clInfo = collectLabels(inputFile);
    if (clInfo != CONFIRM)
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
        if (asminst.verifyInst(curinst) == NEGATION)
        {
            inputStream.close();
            return lineNum;
        }
        lineNum++;
    }

    inputStream.close();
    return CONFIRM;
}

#endif // _RVX_ASSEMBLER_PUB_CPP_