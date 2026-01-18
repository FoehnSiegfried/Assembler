#ifndef _RVX_ASSEMBLER_PRI_CPP_
#define _RVX_ASSEMBLER_PRI_CPP_

#include "RVX_Assembler.h"

void RVX_Assembler::initInst()
{
    for (int i = 0; i < RVX_INSTVOLUME; i++)
    {
        inst[i] = PLACEHOLDER_STRING;
    }
}

void RVX_Assembler::valSetInst(string &val_instLine)
{
    initInst();
    int index = 0;
    string buf;
    for (int i = 0; i < val_instLine.length() && (index < RVX_INSTVOLUME); i++)
    {
        if (val_instLine[i] == ' ')
        {
            inst[index] = buf;
            buf = "";
            index++;
        }
        else
        {
            buf += val_instLine[i];
        }
    }
    if ((buf != "") && (index < RVX_INSTVOLUME))
        inst[index] = buf;
}

int RVX_Assembler::searchKeyWord(string &val_keyWord)
{
    if (ri.searchKeyWord(val_keyWord) == CONFIRM)
        return CONFIRM;
    if (pi.searchKeyWord(val_keyWord) == CONFIRM)
        return CONFIRM;
    return NEGATION;
}

#endif // _RVX_ASSEMBLER_PRI_CPP_