#ifndef _RVX_ASSEMBLER_PRI_CPP_
#define _RVX_ASSEMBLER_PRI_CPP_

#include "RVX_Assembler.h"

#define RVX_ASSEMBLER_PRI_VERSION "2.1.0"

void RVX_Assembler::loadInst(const string &line)
{
    for (int i = 0; i < MAX_RVXINST_VOLUNM; i++)
    {
        curinst[i] = PLACEHOLDER_STRING;
    }
    int index = 0;
    string buf;
    for (int i = 0; i < line.length() && (index < MAX_RVXINST_VOLUNM); i++)
    {
        if (line[i] == ' ')
        {
            curinst[index] = buf;
            buf = "";
            index++;
        }
        else
        {
            buf += line[i];
        }
    }
    if ((buf != "") && (index < MAX_RVXINST_VOLUNM))
        curinst[index] = buf;
}

int RVX_Assembler::collectLabels(const string &inputFile)
{
    ifstream inputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");
    return NEGATION;

    labels.clear();

    int lineNum = 1;
    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (curinst[0] == RVXINST_LABEL)
        {
            if ((labels.ownKey(curinst[1])) || (curinst[1] == PLACEHOLDER_STRING))
                return lineNum;
            labels.insert(curinst[1], index * PC_ONCE_SIZE);
            lineNum++;
            continue;
        }
        index++;
        lineNum++;
    }

    inputStream.close();
    return CONFIRM;
}

int RVX_Assembler::loadLabels()
{
    for (int i = 0; ((i < MAX_RVXINST_VOLUNM) && (curinst[i] != PLACEHOLDER_STRING)); i++)
    {
        if (((!isSignedInteger(curinst[i])) && (asminst.findKey(curinst[i]) == NEGATION)))
        {
            if (labels.ownKey(curinst[i]))
            {
                int labelAddr = labels.search(curinst[i]);
                int32_t offset = labelAddr - (curinstIndex * PC_ONCE_SIZE);
                curinst[i] = to_string(offset);
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