#ifndef _RVX_PSEUDOINST_PUB_CPP_
#define _RVX_PSEUDOINST_PUB_CPP_

#include "PseudoInst.h"

int PseudoInst::getPICodeNum()
{
    return PICodeNum;
}
string PseudoInst::getPICode(int PICodeIndex)
{
    return PICode[PICodeIndex];
}

int PseudoInst::searchKeyWord(string &val_keyWord){
    if(PIMap.find(val_keyWord))
        return CONFIRM;
    return NEGATION;
}

int PseudoInst::verify(string *ptr_inst)
{
    if (PIMap.find(ptr_inst[0]))
    {
        switch (PIMap[ptr_inst[0]].fomart)
        {
        case PIF_INST_REG_IMM:
            
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
    }else{
        return NEGATION;
    }
}
int PseudoInst::interpret(string *ptr_inst)
{
    clearPICode();
    int verifyInfo = verify(ptr_inst);
    if(verifyInfo!=CONFIRM)
        return NEGATION;

    switch(PIMap[ptr_inst[0]].inst){
        case PII_LI:
            return PI_li(ptr_inst);
        default:
            return NEGATION;
    }
}

#endif // _RVX_PSEUDOINST_PUB_CPP_