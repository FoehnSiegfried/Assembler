#ifndef _RVX_ASMINST_PRI_PSEUDO_CPP_
#define _RVX_ASMINST_PRI_PSEUDO_CPP_

#include "RVX_Asminst.h"

#define RVX_ASMINST_PRI_PSEUDO_VERSION "1.0.0"

int RVX_Asminst::pseudo_li(string *inst)
{
    clearCode();
    string instName = "li";
    if ((inst[0] != instName) || !regMap.find(inst[1]) || !isSignedInteger(inst[2]))
    {
        return NEGATION;
    }
    uint32_t imm = stol(inst[2]) & 0xFFFFFFFF;
    int32_t addi_imm = imm & 0xFFF;
    int32_t lui_imm = (imm & 0xFFFFF000) >> 12;
    string lui_inst[3] = {"lui", inst[1], ""};
    string addi_inst[4] = {"addi", inst[1], "x0", ""};
    if ((lui_imm != 0) && (addi_imm & 0x800))
        lui_imm += 0x1;
    lui_inst[2] = to_string(lui_imm);
    addi_inst[3] = to_string(addi_imm);
    if (lui_imm != 0)
    {
        code[codeNum] = rv32i.RV32I(lui_inst);
        codeNum++;
    }
    if (addi_imm != 0)
    {
        code[codeNum] = rv32i.RV32I(addi_inst);
        codeNum++;
    }
    return CONFIRM;
}

#endif // _RVX_ASMINST_PRI_PSEUDO_CPP_