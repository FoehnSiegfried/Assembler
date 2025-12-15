#ifndef _RVX_ASSEMBLER_PRI_CPP_
#define _RVX_ASSEMBLER_PRI_CPP_

#include "RVX_Assembler.h"

void RVX_Assembler::loadInst(const string &line)
{
    for (int i = 0; i < 4; i++)
        inst[i] = "";
    int index = 0;
    string buf;
    for (int i = 0; i < line.length() && (index < 4); i++)
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
    if ((buf != "") && (index < 4))
        inst[index] = buf;
}

int RVX_Assembler::collectLabels(const string &inputFile)
{
    ifstream inputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");

    labels->clear();

    int lineNum = 1;
    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        loadInst(lineBuf);
        if (inst[0] == TAG_LABEL)
        {
            if(labels->ownKey(inst[1]))
                return lineNum;
            labels->insert(inst[1], index * 4);
            lineNum++;
            continue;
        }
        index++;
        lineNum++;
    }

    inputStream.close();
    return 0;
}

bool RVX_Assembler::verifyInst()
{
    if (inst[0] == TAG_LABEL)
    {
        if ((inst[1] == "") || isSignedInteger(inst[1]))
            return false;
        return true;
    }

    if (RV32IMap.find(inst[0]))
    {
        short format = RV32IMap[inst[0]].instFormat;
        switch (format)
        {
        case TYPE_R:
            if (inst[1] == "" || inst[2] == "" || inst[3] == "")
                return false;
            if (!regMap.find(inst[1]) || !regMap.find(inst[2]) || !regMap.find(inst[3]))
                return false;
            return true;
        case TYPE_I:
            if (inst[1] == "" || inst[2] == "" || inst[3] == "")
                return false;
            if (!regMap.find(inst[1]) || !regMap.find(inst[2]))
                return false;
            if(!isSignedInteger(inst[3])&&!labels->ownKey(inst[3]))
                return false;
            return true;
        case TYPE_S:
            if (inst[1] == "" || inst[2] == "" || inst[3] == "")
                return false;
            if (!regMap.find(inst[1]) || !regMap.find(inst[3]))
                return false;
            if(!isSignedInteger(inst[2])&&!labels->ownKey(inst[2]))
                return false;
            return true;
        case TYPE_B:
            if (inst[1] == "" || inst[2] == "" || inst[3] == "")
                return false;
            if (!regMap.find(inst[1]) || !regMap.find(inst[2]))
                return false;
            if(!isSignedInteger(inst[3])&&!labels->ownKey(inst[3]))
                return false;
            return true;
        case TYPE_U:
            if (inst[1] == "" || inst[2] == "")
                return false;
            if (!regMap.find(inst[1]))
                return false;
            if(!isSignedInteger(inst[2])&&!labels->ownKey(inst[2]))
                return false;
            return true;
        case TYPE_J:
            if (inst[1] == "" || inst[2] == "")
                return false;
            if (!regMap.find(inst[1]))
                return false;
            if(!isSignedInteger(inst[2])&&!labels->ownKey(inst[2]))
                return false;
            return true;
        default:
            return false;
        }
    }
    else
    {
        return false;
    }
}

void RVX_Assembler::loadLabels(int instAddr)
{
    if (RV32IMap.find(inst[0]))
    {
        short format = RV32IMap[inst[0]].instFormat;
        switch(format)
        {
            case TYPE_I:
                if(!isSignedInteger(inst[3]) && labels->ownKey(inst[3]))
                {
                    int labelAddr = labels->search(inst[3]);
                    int32_t offset = labelAddr - (instAddr*4);
                    inst[3] = to_string(offset);
                }
                return;
            case TYPE_S:
                if(!isSignedInteger(inst[2]) && labels->ownKey(inst[2]))
                {
                    int labelAddr = labels->search(inst[2]);
                    int32_t offset = labelAddr - (instAddr*4);
                    inst[2] = to_string(offset);
                }
                return;
            case TYPE_B:
                if(!isSignedInteger(inst[3]) && labels->ownKey(inst[3]))
                {
                    int labelAddr = labels->search(inst[3]);
                    int32_t offset = labelAddr - (instAddr*4);
                    inst[3] = to_string(offset);
                }
                return;
            case TYPE_U:
                if(!isSignedInteger(inst[2]) && labels->ownKey(inst[2]))
                {
                    int labelAddr = labels->search(inst[2]);
                    int32_t offset = labelAddr - (instAddr*4);
                    inst[2] = to_string(offset);
                }
                return;
            case TYPE_J:
            if(!isSignedInteger(inst[2]) && labels->ownKey(inst[2]))
                {
                    int labelAddr = labels->search(inst[2]);
                    int32_t offset = labelAddr - (instAddr*4);
                    inst[2] = to_string(offset);
                }
                return;
            default:
                return;
        }
    }
}

#endif // _RVX_ASSEMBLER_PRI_CPP_