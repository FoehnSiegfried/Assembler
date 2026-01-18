#ifndef _RVX_ASMINST_PUB_CPP_
#define _RVX_ASMINST_PUB_CPP_

#include "RVX_Asminst.h"

#define RVX_ASMINST_PUB_VERSION "1.0.0"

int RVX_Asminst::getCodeNum()
{
    return codeNum;
}
uint32_t RVX_Asminst::getCode(int codeIndex)
{
    return code[codeIndex];
}

int RVX_Asminst::findKey(string &key)
{
    if (findKeyRVInst(key) == CONFIRM)
        return CONFIRM;
    if (AsminstMap.find(key))
        return CONFIRM;

    return NEGATION;
}

int RVX_Asminst::verifyInst(string *inst)
{
    if (verifyRVInstMap(inst) == CONFIRM)
        return CONFIRM;
    if (AsminstMap.find(inst[0]))
    {
        switch (AsminstMap[inst[0]].ap)
        {
        case AP_INST_REG_NUM:
            if (!regMap.find(inst[1]))
            {
                return NEGATION;
            }
            if (!isSignedInteger(inst[2]))
            {
                return NEGATION;
            }
            return CONFIRM;
            break;
        default:
            return NEGATION;
            break;
        }
    }
    else
    {
        return NEGATION;
    }
}

int RVX_Asminst::interpret(string *inst)
{
    clearCode();
    if (verifyInst(inst) == NEGATION)
        return NEGATION;
    if (AsminstMap.find(inst[0]))
    {
        switch (AsminstMap[inst[0]].af)
        {
        case AF_LI:
            if (pseudo_li(inst) == NEGATION)
            {
                clearCode();
                return NEGATION;
            }
            return CONFIRM;
            break;
        default:
            return NEGATION;
            break;
        }
    }
    else if (RV32IMap.find(inst[0]))
    {
        codeNum = 1;
        code[0] = rv32i.RV32I(inst);
        if (code[0] == RVX_ERROR_INST)
        {
            clearCode();
            return NEGATION;
        }
        return CONFIRM;
    }
    else
    {
        return NEGATION;
    }
}

#endif // _RVX_ASMINST_PUB_CPP_