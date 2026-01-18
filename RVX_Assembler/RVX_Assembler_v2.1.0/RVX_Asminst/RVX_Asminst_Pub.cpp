#ifndef _RVX_ASMINST_PUB_CPP_
#define _RVX_ASMINST_PUB_CPP_

#include "RVX_Asminst.h"

#define RVX_ASMINST_PUB_VERSION "2.1.0"

int RVX_Asminst::getAsminstNum()
{
    return asminstNum;
}

uint32_t RVX_Asminst::getAsminst(int asminstIndex)
{
    return asminst[asminstIndex];
}

int RVX_Asminst::verifyInst(string *inst)
{
    if (AsminstMap.find(inst[0]))
    {
        switch (AsminstMap[inst[0]].afp)
        {
        case AFP_OP_RD_IMM:
            if ((inst[0] == PLACEHOLDER_STRING) || (inst[1] == PLACEHOLDER_STRING) || (inst[2] == PLACEHOLDER_STRING))
            {
                return NEGATION;
            }
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
    else if (RV32IMap.find(inst[0]))
    {
        short format = RV32IMap[inst[0]].instFormat;
        switch (format)
        {
        case TYPE_R:
            if (inst[1] == PLACEHOLDER_STRING || inst[2] == PLACEHOLDER_STRING || inst[3] == PLACEHOLDER_STRING)
                return NEGATION;
            if (!regMap.find(inst[1]) || !regMap.find(inst[2]) || !regMap.find(inst[3]))
                return NEGATION;
            return CONFIRM;
        case TYPE_I:
            if (inst[1] == PLACEHOLDER_STRING || inst[2] == PLACEHOLDER_STRING || inst[3] == PLACEHOLDER_STRING)
                return NEGATION;
            if (!regMap.find(inst[1]) || !regMap.find(inst[2]))
                return NEGATION;
            if (!isSignedInteger(inst[3]))
                return NEGATION;
            return CONFIRM;
        case TYPE_S:
            if (inst[1] == PLACEHOLDER_STRING || inst[2] == PLACEHOLDER_STRING || inst[3] == PLACEHOLDER_STRING)
                return NEGATION;
            if (!regMap.find(inst[1]) || !regMap.find(inst[3]))
                return NEGATION;
            if (!isSignedInteger(inst[2]))
                return NEGATION;
            return CONFIRM;
        case TYPE_B:
            if (inst[1] == PLACEHOLDER_STRING || inst[2] == PLACEHOLDER_STRING || inst[3] == PLACEHOLDER_STRING)
                return NEGATION;
            if (!regMap.find(inst[1]) || !regMap.find(inst[2]))
                return NEGATION;
            if (!isSignedInteger(inst[3]))
                return NEGATION;
            return CONFIRM;
        case TYPE_U:
            if (inst[1] == PLACEHOLDER_STRING || inst[2] == PLACEHOLDER_STRING)
                return NEGATION;
            if (!regMap.find(inst[1]))
                return NEGATION;
            if (!isSignedInteger(inst[2]))
                return NEGATION;
            return CONFIRM;
        case TYPE_J:
            if (inst[1] == PLACEHOLDER_STRING || inst[2] == PLACEHOLDER_STRING)
                return NEGATION;
            if (!regMap.find(inst[1]))
                return NEGATION;
            if (!isSignedInteger(inst[2]))
                return NEGATION;
            return CONFIRM;
        default:
            return NEGATION;
        }
    }
    else
    {
        return NEGATION;
    }
}

int RVX_Asminst::RVX_Asm(string *inst)
{
    if(verifyInst(inst)==NEGATION){
        return NEGATION;
    }
    clearAsminst();
    string instName = inst[0];
    if (AsminstMap.find(instName))
    {
        switch (AsminstMap[instName].af)
        {
        case AF_LI:
            return pseudo_li(inst);
            break;
        default:
            return NEGATION;
            break;
        }
    }
    else if (RV32IMap.find(instName))
    {
        asminstNum = 1;
        asminst[0] = rv32i.RV32I(inst);
        if (asminst[0] == RVX_ERROR_INST)
        {
            asminstNum = 0;
            return NEGATION;
        }
        return CONFIRM;
    }
}

#endif // _RVX_ASMINST_PUB_CPP_