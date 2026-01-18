#ifndef _RVX_ASMINST_PRI_CPP_
#define _RVX_ASMINST_PRI_CPP_

#include "RVX_Asminst.h"

#define RVX_ASMINST_PRI_VERSION "1.0.0"

void RVX_Asminst::clearCode()
{
    codeNum = 0;
    for (int i = 0; i < ASMINST_MAX_CODE_VOLUME; i++)
    {
        code[i] = 0x00000000;
    }
}

int RVX_Asminst::findKeyRVInst(string &key){
    if(regMap.find(key))
        return CONFIRM;
    if(RV32IMap.find(key))
        return CONFIRM;

    return NEGATION;
}

int RVX_Asminst::verifyRVInstMap(string *inst)
{
    short format;

    if (RV32IMap.find(inst[0]))
        format = RV32IMap[inst[0]].instFormat;

    switch (format)
    {
    case TYPE_R:
        if (!regMap.find(inst[1]) || !regMap.find(inst[2]) || !regMap.find(inst[3]))
            return NEGATION;
        return CONFIRM;
    case TYPE_I:
        if (!regMap.find(inst[1]) || !regMap.find(inst[2]))
            return NEGATION;
        if (!isSignedInteger(inst[3]))
            return NEGATION;
        return CONFIRM;
    case TYPE_S:
        if (!regMap.find(inst[1]) || !regMap.find(inst[3]))
            return NEGATION;
        if (!isSignedInteger(inst[2]))
            return NEGATION;
        return CONFIRM;
    case TYPE_B:
        if (!regMap.find(inst[1]) || !regMap.find(inst[2]))
            return NEGATION;
        if (!isSignedInteger(inst[3]))
            return NEGATION;
        return CONFIRM;
    case TYPE_U:
        if (!regMap.find(inst[1]))
            return NEGATION;
        if (!isSignedInteger(inst[2]))
            return NEGATION;
        return CONFIRM;
    case TYPE_J:
        if (!regMap.find(inst[1]))
            return NEGATION;
        if (!isSignedInteger(inst[2]))
            return NEGATION;
        return CONFIRM;
    default:
        return NEGATION;
    }
}

#endif // _RVX_ASMINST_PRI_CPP_