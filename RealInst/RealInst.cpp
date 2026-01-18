#ifndef _RVX_REALINST_CPP_
#define _RVX_REALINST_CPP_

#include "RealInst.h"

int RealInst::searchKeyWord(string &val_keyWord){
    if(RVRegMap.find(val_keyWord))
        return CONFIRM;
    if(RV32IMap.find(val_keyWord))
        return CONFIRM;
    return NEGATION;
}

int RealInst::searchRVInstFormat(string val_instName)
{
    if (RV32IMap.find(val_instName))
    {
        return RV32IMap[val_instName].instFormat;
    }
    else
    {
        return NEGATION;
    }
}

// ---------------------------------------------------

int RealInst::verify(string *ptr_inst)
{
    int instFormat = searchRVInstFormat(ptr_inst[0]);
    if (instFormat == NEGATION)
    {
        return NEGATION;
    }
    switch (instFormat)
    {
    case TYPE_R:
        if ((ptr_inst[0] == PLACEHOLDER_STRING) || (ptr_inst[1] == PLACEHOLDER_STRING) || (ptr_inst[2] == PLACEHOLDER_STRING) || (ptr_inst[3] == PLACEHOLDER_STRING))
            return NEGATION;
        if (!((RVRegMap.find(ptr_inst[1])) && (RVRegMap.find(ptr_inst[2])) && (RVRegMap.find(ptr_inst[3]))))
            return NEGATION;
        return CONFIRM;
    case TYPE_I:
        if ((ptr_inst[0] == PLACEHOLDER_STRING) || (ptr_inst[1] == PLACEHOLDER_STRING) || (ptr_inst[2] == PLACEHOLDER_STRING) || (ptr_inst[3] == PLACEHOLDER_STRING))
            return NEGATION;
        if (!((RVRegMap.find(ptr_inst[1])) && (RVRegMap.find(ptr_inst[2]))))
            return NEGATION;
        if (!isSignedInteger(ptr_inst[3]))
            return NEGATION;
        return CONFIRM;
    case TYPE_S:
        if ((ptr_inst[0] == PLACEHOLDER_STRING) || (ptr_inst[1] == PLACEHOLDER_STRING) || (ptr_inst[2] == PLACEHOLDER_STRING) || (ptr_inst[3] == PLACEHOLDER_STRING))
            return NEGATION;
        if (!((RVRegMap.find(ptr_inst[1])) && (RVRegMap.find(ptr_inst[3]))))
            return NEGATION;
        if (!isSignedInteger(ptr_inst[2]))
            return NEGATION;
        return CONFIRM;
    case TYPE_B:
        if ((ptr_inst[0] == PLACEHOLDER_STRING) || (ptr_inst[1] == PLACEHOLDER_STRING) || (ptr_inst[2] == PLACEHOLDER_STRING) || (ptr_inst[3] == PLACEHOLDER_STRING))
            return NEGATION;
        if (!((RVRegMap.find(ptr_inst[1])) && (RVRegMap.find(ptr_inst[2]))))
            return NEGATION;
        if (!isSignedInteger(ptr_inst[3]))
            return NEGATION;
        return CONFIRM;
    case TYPE_U:
        if ((ptr_inst[0] == PLACEHOLDER_STRING) || (ptr_inst[1] == PLACEHOLDER_STRING) || (ptr_inst[2] == PLACEHOLDER_STRING))
            return NEGATION;
        if (!RVRegMap.find(ptr_inst[1]))
            return NEGATION;
        if (!isSignedInteger(ptr_inst[2]))
            return NEGATION;
        return CONFIRM;
    case TYPE_J:
        if ((ptr_inst[0] == PLACEHOLDER_STRING) || (ptr_inst[1] == PLACEHOLDER_STRING) || (ptr_inst[2] == PLACEHOLDER_STRING))
            return NEGATION;
        if (!RVRegMap.find(ptr_inst[1]))
            return NEGATION;
        if (!isSignedInteger(ptr_inst[2]))
            return NEGATION;
        return CONFIRM;
    default:
        return NEGATION;
    }
}
uint32_t RealInst::interpret(string *ptr_inst)
{
    int verifyInfo = verify(ptr_inst);
    if (verifyInfo != CONFIRM)
        return NEGATION;

    string instName = ptr_inst[0];
    if (RV32IMap.find(instName))
        return rv32i.interpret(ptr_inst);
    else
        return RVX_ERROR_INST;
}

#endif // _REALINST_CPP_