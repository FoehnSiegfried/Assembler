#ifndef _RA_RV32I_CPP_
#define _RA_RV32I_CPP_

#include "RVX_Assembler.h"
#include "RVX_Info.h"

static Map<string, RVInst> RV32IMap = {
    {"add", {"add", TYPE_R, 0b0110011, 0x0, 0x00}},
    {"sub", {"sub", TYPE_R, 0b0110011, 0x0, 0x20}},
    {"xor", {"xor", TYPE_R, 0b0110011, 0x4, 0x00}},
    {"or", {"or", TYPE_R, 0b0110011, 0x6, 0x00}},
    {"and", {"and", TYPE_R, 0b0110011, 0x7, 0x00}},
    {"sll", {"sll", TYPE_R, 0b0110011, 0x1, 0x00}},
    {"srl", {"srl", TYPE_R, 0b0110011, 0x5, 0x00}},
    {"sra", {"sra", TYPE_R, 0b0110011, 0x5, 0x20}},
    {"slt", {"slt", TYPE_R, 0b0110011, 0x2, 0x00}},
    {"sltu", {"sltu", TYPE_R, 0b0110011, 0x3, 0x00}},

    {"addi", {"addi", TYPE_I, 0b0010011, 0x0, 0x00}},
    {"xori", {"xori", TYPE_I, 0b0010011, 0x4, 0x00}},
    {"ori", {"ori", TYPE_I, 0b0010011, 0x6, 0x00}},
    {"andi", {"andi", TYPE_I, 0b0010011, 0x7, 0x00}},
    {"slli", {"slli", TYPE_I, 0b0010011, 0x1, 0x00}},
    {"srli", {"srli", TYPE_I, 0b0010011, 0x5, 0x00}},
    {"srai", {"srai", TYPE_I, 0b0010011, 0x5, 0x20}},
    {"slti", {"slti", TYPE_I, 0b0010011, 0x2, 0x00}},
    {"sltiu", {"sltiu", TYPE_I, 0b0010011, 0x3, 0x00}},

    {"lb", {"lb", TYPE_I, 0b0000011, 0x0, 0x0}},
    {"lh", {"lh", TYPE_I, 0b0000011, 0x1, 0x0}},
    {"lw", {"lw", TYPE_I, 0b0000011, 0x2, 0x0}},
    {"lbu", {"lbu", TYPE_I, 0b0000011, 0x4, 0x0}},
    {"lhu", {"lhu", TYPE_I, 0b0000011, 0x5, 0x0}},

    {"sb", {"sb", TYPE_S, 0b0100011, 0x0, 0x0}},
    {"sh", {"sh", TYPE_S, 0b0100011, 0x1, 0x0}},
    {"sw", {"sw", TYPE_S, 0b0100011, 0x2, 0x0}},

    {"beq", {"beq", TYPE_B, 0b1100011, 0x0, 0x0}},
    {"bne", {"bne", TYPE_B, 0b1100011, 0x1, 0x0}},
    {"blt", {"blt", TYPE_B, 0b1100011, 0x4, 0x0}},
    {"bge", {"bge", TYPE_B, 0b1100011, 0x5, 0x0}},
    {"bltu", {"bltu", TYPE_B, 0b1100011, 0x6, 0x0}},
    {"bgeu", {"bgeu", TYPE_B, 0b1100011, 0x7, 0x0}},

    {"jal", {"jal", TYPE_J, 0b1101111, 0x0, 0x0}},
    {"jalr", {"jalr", TYPE_I, 0b1100111, 0x0, 0x0}},

    {"lui", {"lui", TYPE_U, 0b0110111, 0x0, 0x0}},
    {"auipc", {"auipc", TYPE_U, 0b0010111, 0x0, 0x0}},

    {"ecall", {"ecall", TYPE_I, 0b1110011, 0x0, 0x0}},
    {"ebreak", {"ebreak", TYPE_I, 0b1110011, 0x0, 0x1}}};

uint32_t RV32I_Type_R(string *inst)
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
uint32_t RV32I_Type_I(string *inst)
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
uint32_t RV32I_Type_S(string *inst)
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
uint32_t RV32I_Type_B(string *inst)
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
uint32_t RV32I_Type_U(string *inst)
{
    string instName = inst[0];
    string rd = inst[1];
    int32_t imm = stoll(inst[2]);

    uint32_t val_opcode = (RV32IMap[instName].opcode & 0x7F);
    uint32_t val_rd = (regMap[rd] & 0x1F);
    int32_t val_imm = (imm << 12);

    return val_imm | (val_rd << 7) | val_opcode;
}
uint32_t RV32I_Type_J(string *inst)
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

uint32_t RVX_Assembler::RV32I()
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
        return 0; // error
    }
}

#endif // _RA_RV32I_CPP_