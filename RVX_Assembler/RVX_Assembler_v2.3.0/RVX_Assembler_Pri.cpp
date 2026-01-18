#ifndef _RVX_ASSEMBLER_PRI_CPP_
#define _RVX_ASSEMBLER_PRI_CPP_

#include "RVX_Assembler.h"

#define RVX_ASSEMBLER_PRI_VERSION "2.3.0"

void RVX_Assembler::clearInst()
{
    for (int i = 0; i < RVX_MAX_INSTVOLUNM; i++)
    {
        inst[i] = PLACEHOLDER_STRING;
    }
}

void RVX_Assembler::loadInst(const string &line)
{
    clearInst();
    int index = 0;
    string buf;
    for (int i = 0; i < line.length() && (index < RVX_MAX_INSTVOLUNM); i++)
    {
        if (line[i] == ' ')
        {
            inst[index] = buf;
            buf = "";
            index++;
        }
        else
        {
            buf += line[i];
        }
    }
    if ((buf != "") && (index < RVX_MAX_INSTVOLUNM))
        inst[index] = buf;
}

int RVX_Assembler::findKey(string &key)
{
    if (asminst.findKey(key) == CONFIRM)
        return CONFIRM;
    if (RVXInstMap.find(key))
        return CONFIRM;

    return NEGATION;
}

int RVX_Assembler::verifyInst()
{
    if (asminst.verifyInst(inst) == CONFIRM)
        return CONFIRM;

    if (RVXInstMap.find(inst[0]))
    {
        switch (RVXInstMap[inst[0]].rp)
        {
        case RP_INST_NONUM:
            if (!isSignedInteger(inst[1]))
            {
                return CONFIRM;
            }
            return NEGATION;
            break;
        default:
            return NEGATION;
        }
    }
    return NEGATION;
}

int RVX_Assembler::collectLabels(const string &inputFile)
{
    ifstream inputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");
    labels.clear();
    int lineNum = 1;
    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (inst[0] == RVX_INST_LABEL)
        {
            if ((labels.ownKey(inst[1])) || (inst[1] == PLACEHOLDER_STRING))
                return lineNum;
            labels.insert(inst[1], index * RVX_PC_ONCE_SIZE);
            lineNum++;
            continue;
        }
        index++;
        lineNum++;
    }

    inputStream.close();
    return CONFIRM;
}

int RVX_Assembler::loadLabels(int instIndex)
{
    if (inst[0] == RVX_INST_LABEL)
        return CONFIRM;
    for (int i = 0; ((i < RVX_MAX_INSTVOLUNM) && (inst[i] != PLACEHOLDER_STRING)); i++)
    {
        if (((!isSignedInteger(inst[i])) && (findKey(inst[i]) == NEGATION)))
        {
            if (labels.ownKey(inst[i]))
            {
                int labelAddr = labels.search(inst[i]);
                int32_t offset = labelAddr - (instIndex * RVX_PC_ONCE_SIZE);
                inst[i] = to_string(offset);
            }
            else
            {
                return NEGATION;
            }
        }
    }
    return CONFIRM;
}

#endif // _RVX_ASSEMBLER_PRI_CPP_