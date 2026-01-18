#ifndef _RVX_PSEUDOINST_PRI_CPP_
#define _RVX_PSEUDOINST_PRI_CPP_

#include "PseudoInst.h"

void PseudoInst::clearPICode()
{
    PICodeNum = 0;
    for (int i = 0; i < PI_CODE_VOLUME; i++)
    {
        PICode[i] = PLACEHOLDER_STRING;
    }
}

int PseudoInst::PI_li(string *ptr_inst)
{
    clearPICode();
    string instName = "li";
    if ((ptr_inst[0] != instName) || !RVRegMap.find(ptr_inst[1]) || !isSignedInteger(ptr_inst[2]))
        return NEGATION;
    uint32_t imm = stoll(ptr_inst[2]) & 0xFFFFFFFF;
    int32_t addi_imm = imm & 0xFFF;
    int32_t lui_imm = (imm & 0xFFFFF000) >> 12;
    string lui_inst[3] = {"lui", ptr_inst[1], ""};
    string addi_inst[4] = {"addi", ptr_inst[1], "x0", ""};
    if ((lui_imm != 0) && (addi_imm & 0x800))
        lui_imm += 0x1;
    lui_inst[2] = to_string(lui_imm);
    addi_inst[3] = to_string(addi_imm);
    if (lui_imm != 0)
    {
        PICode[PICodeNum] = lui_inst[0] + " " + lui_inst[1] + " " + lui_inst[2];
        PICodeNum++;
    }
    if (addi_imm != 0)
    {
        PICode[PICodeNum] = addi_inst[0] + " " + addi_inst[1] + " " + addi_inst[2] + " " + addi_inst[3];
        PICodeNum++;
    }
    return CONFIRM;
}

#endif // _RVX_PSEUDOINST_PRI_CPP_