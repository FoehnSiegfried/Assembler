#ifndef _RVX_RV32I_CPP_
#define _RVX_RV32I_CPP_

#include "RVX_RV32I.h"

/*
RV32I指令集
R,I,S,B,U,J
*/

uint32_t RVX_RV32I::RV32I_Type_R(string *inst)
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
uint32_t RVX_RV32I::RV32I_Type_I(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    string rs1 = inst[2];
    int32_t imm = stol(inst[3]);

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
uint32_t RVX_RV32I::RV32I_Type_S(string *inst)
{
    string instName = inst[0];
    string rs2 = inst[1];
    int32_t imm = stol(inst[2]);
    string rs1 = inst[3];

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    int32_t val_imm4_0 = (imm & 0x1F);
    uint32_t val_funct3 = (RV32IMap[instName].funct3 & 0x7);
    uint32_t val_rs1 = (regMap[rs1] & 0x1F);
    uint32_t val_rs2 = (regMap[rs2] & 0x1F);
    int32_t val_imm11_5 = (imm >> 5);

    return (val_imm11_5 << 25) | (val_rs2 << 20) | (val_rs1 << 15) | (val_funct3 << 12) | (val_imm4_0 << 7) | val_opcode;
}
uint32_t RVX_RV32I::RV32I_Type_B(string *inst)
{
    string instName = inst[0];
    string rs1 = inst[1];
    string rs2 = inst[2];
    int32_t imm = stol(inst[3]);

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
uint32_t RVX_RV32I::RV32I_Type_U(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    int32_t imm = stol(inst[2]);

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    uint32_t val_rd = (regMap[rd] & 0x1F);
    int32_t val_imm = (imm << 12);

    return val_imm | (val_rd << 7) | val_opcode;
}
uint32_t RVX_RV32I::RV32I_Type_J(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    int32_t imm = stol(inst[2]);

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    uint32_t val_rd = (regMap[rd] & 0x1F);
    int32_t val_imm19_12 = ((imm & 0xFF000) >> 12);
    int32_t val_imm11 = ((imm & 0x800) >> 11);
    int32_t val_imm10_1 = ((imm & 0x7FE) >> 1);
    int32_t val_imm20 = ((imm & 0x100000) >> 20);

    return (val_imm20 << 31) | (val_imm10_1 << 21) | (val_imm11 << 20) | (val_imm19_12 << 12) | (val_rd << 7) | val_opcode;
}

uint32_t RVX_RV32I::RV32I(string* inst)
{
    switch (RV32IMap[inst[0]].instFormat)
    {
    case TYPE_R:
        return RV32I_Type_R(inst);
    case TYPE_I:
        return RV32I_Type_I(inst);
    case TYPE_S:
        return RV32I_Type_S(inst);
    case TYPE_B:
        return RV32I_Type_B(inst);
    case TYPE_U:
        return RV32I_Type_U(inst);
    case TYPE_J:
        return RV32I_Type_J(inst);
    default:
        return RVX_ERROR_INST; // error
    }
}

#endif // _RA_RV32I_CPP_