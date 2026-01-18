#ifndef _RVX_ASMINST_PRI_PSEUDO_CPP_
#define _RVX_ASMINST_PRI_PSEUDO_CPP_

#include "RVX_Asminst.h"

#define RVX_ASMINST_PRI_PSEUDO_VERSION "2.1.0"

int RVX_Asminst::pseudo_li(string *inst)
{
    string instName = "li";
    if ((inst[0] != instName) || !regMap.find(inst[1]) || !isSignedInteger(inst[2]))
    {
        return NEGATION;
    }
    uint32_t rd = regMap[inst[1]];
    int32_t imm = stol(inst[2]) & 0xFFFFFFFF;
    uint32_t low12 = imm & 0xFFF;
    uint32_t high20 = imm & 0xFFFFF000;
    int32_t lui_imm;
    int32_t addi_imm;
    if (high20)
    {
        if (low12)
        {
            // lui+addi
            if ((low12 & 0x800))
            {
                low12 -= 0x1000;
                high20 += 0x1000;
            }
            else
            {
            }
        }
        else
        {
            // lui
        }
    }
    else
    {
        if (low12)
        {
            // addi
        }
        else
        {
            // addi rd x0 0
        }
    }
}

#endif // _RVX_ASMINST_PRI_PSEUDO_CPP_