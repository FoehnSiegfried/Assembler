#ifndef _RVXASSEMBLER_PRI_CPP_
#define _RVXASSEMBLER_PRI_CPP_

#include "RVXAssembler.h"

string *RVXAssembler::instLoad(string &val)
{
    int instIndex = 0;
    string *inst = new string[4];
    string buf;
    for (int i = 0; i < val.length(); i++)
    {
        if (val[i] == ' ')
        {
            inst[instIndex] = buf;
            buf = "";
            instIndex++;
            if (instIndex >= 4)
                break;
        }
        else
        {
            buf += val[i];
        }
    }
    if (instIndex < 4)
        inst[instIndex] = buf;
    return inst;
}

bool RVXAssembler::isSignedInteger(const string &str)
{
    if (str.empty())
        return false;
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+')
    {
        start = 1;
        if (str.length() == 1)
            return false;
    }
    for (size_t i = start; i < str.length(); i++)
    {
        if (!isdigit(static_cast<unsigned char>(str[i])))
        {
            return false;
        }
    }
    return true;
}

uint32_t RVXAssembler::takeRV32ITypeR(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    string rs1 = inst[2];
    string rs2 = inst[3];

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    uint32_t val_rd = (regMap[rd] & 0x1F);
    uint32_t val_funct3 = (RV32IMap[instName].funct3 & 0x7);
    uint32_t val_rs1 = (regMap[rs1] & 0x1F);
    uint32_t val_rs2 = (regMap[rs2] & 0x1F);
    uint32_t val_funct7 = (RV32IMap[instName].funct7 & 0x7F);

    return (val_funct7 << 25) | (val_rs2 << 20) | (val_rs1 << 15) | (val_funct3 << 12) | (val_rd << 7) | val_opcode;
}
uint32_t RVXAssembler::takeRV32ITypeI(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    string rs1 = inst[2];
    int32_t imm = stoll(inst[3]);

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    uint32_t val_rd = (regMap[rd] & 0x1F);
    uint32_t val_funct3 = (RV32IMap[instName].funct3 & 0x7);
    uint32_t val_rs1 = (regMap[rs1] & 0x1F);
    int32_t val_imm;
    uint32_t x20 = 0x20;
    if (instName == "srai")
        val_imm = (imm & 0x1F) | (x20 << 5);
    else if ((instName == "slli") || (instName == "srli"))
        val_imm = (imm & 0x1F);
    else
        val_imm = imm;

    return (val_imm << 20) | (val_rs1 << 15) | (val_funct3 << 12) | (val_rd << 7) | val_opcode;
}
uint32_t RVXAssembler::takeRV32ITypeS(string *inst)
{
    string instName = inst[0];
    string rs2 = inst[1];
    int32_t imm = stoll(inst[2]);
    string rs1 = inst[3];

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    int32_t val_imm4_0 = (imm & 0x1F);
    uint32_t val_funct3 = (RV32IMap[instName].funct3 & 0x7);
    uint32_t val_rs1 = (regMap[rs1] & 0x1F);
    uint32_t val_rs2 = (regMap[rs2] & 0x1F);
    int32_t val_imm11_5 = (imm >> 5);

    return (val_imm11_5 << 25) | (val_rs2 << 20) | (val_rs1 << 15) | (val_funct3 << 12) | (val_imm4_0 << 7) | val_opcode;
}
uint32_t RVXAssembler::takeRV32ITypeB(string *inst)
{
    string instName = inst[0];
    string rs1 = inst[1];
    string rs2 = inst[2];
    int32_t imm = stoll(inst[3]);

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    int32_t val_imm11 = ((imm & 0x800) >> 11);
    int32_t val_imm4_1 = ((imm & 0x1E) >> 1);
    uint32_t val_funct3 = (RV32IMap[instName].funct3 & 0x7);
    uint32_t val_rs1 = (regMap[rs1] & 0x1F);
    uint32_t val_rs2 = (regMap[rs2] & 0x1F);
    int32_t val_imm10_5 = ((imm & 0x7E0) >> 5);
    int32_t val_imm12 = ((imm & 0x1000) >> 12);

    return (val_imm12 << 31) | (val_imm10_5 << 25) | (val_rs2 << 20) | (val_rs1 << 15) | (val_funct3 << 12) | (val_imm4_1 << 8) | (val_imm11 << 7) | val_opcode;
}
uint32_t RVXAssembler::takeRV32ITypeU(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    int32_t imm = stoll(inst[2]);

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    uint32_t val_rd = (regMap[rd] & 0x1F);
    int32_t val_imm = (imm << 12);

    return val_imm | (val_rd << 7) | val_opcode;
}
uint32_t RVXAssembler::takeRV32ITypeJ(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    int32_t imm = stoll(inst[2]);

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    uint32_t val_rd = (regMap[rd] & 0x1F);
    int32_t val_imm19_12 = ((imm & 0xFF000) >> 12);
    int32_t val_imm11 = ((imm & 0x800) >> 11);
    int32_t val_imm10_1 = ((imm & 0x7FE) >> 1);
    int32_t val_imm20 = ((imm & 0x100000) >> 20);

    return (val_imm20 << 31) | (val_imm10_1 << 21) | (val_imm11 << 20) | (val_imm19_12 << 12) | (val_rd << 7) | val_opcode;
}
uint32_t RVXAssembler::instCompileSelect(string *inst)
{
    switch (RV32IMap[inst[0]].instFormat)
    {
    case TYPE_R:
        return takeRV32ITypeR(inst);
    case TYPE_I:
        return takeRV32ITypeI(inst);
    case TYPE_S:
        return takeRV32ITypeS(inst);
    case TYPE_B:
        return takeRV32ITypeB(inst);
    case TYPE_U:
        return takeRV32ITypeU(inst);
    case TYPE_J:
        return takeRV32ITypeJ(inst);
    default:
        return 0x00000013;
    }
}

bool RVXAssembler::checkInst(string *inst)
{
    if (!(RV32IMap.find(inst[0])))
        return false;
    int type = RV32IMap[inst[0]].instFormat;
    switch (type)
    {
    case TYPE_R:
        if (!((regMap.find(inst[1])) && (regMap.find(inst[2])) && (regMap.find(inst[3]))))
            return false;
        break;
    case TYPE_I:
        if (!((regMap.find(inst[1])) && (regMap.find(inst[2])) && (isSignedInteger(inst[3]))))
            return false;
        break;
    case TYPE_S:
        if (!((regMap.find(inst[1])) && (isSignedInteger(inst[2])) && (regMap.find(inst[3]))))
            return false;
        break;
    case TYPE_B:
        if (!((regMap.find(inst[1])) && (regMap.find(inst[2])) && (isSignedInteger(inst[3]))))
            return false;
        break;
    case TYPE_U:
        if (!((regMap.find(inst[1])) && (isSignedInteger(inst[2]))))
            return false;
        break;
    case TYPE_J:
        if (!((regMap.find(inst[1])) && (isSignedInteger(inst[2]))))
            return false;
        break;
    default:
        return false;
    }
    return true;
}

#endif