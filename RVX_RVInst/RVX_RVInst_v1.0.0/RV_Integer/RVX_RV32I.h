#ifndef _RVX_RV32I_H_
#define _RVX_RV32I_H_

#include "../RVX_Info.h"

static Map<string, RVInst_Info> RV32IMap = {
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

class RVX_RV32I
{
private:
    uint32_t RV32I_Type_R(string *inst);
    uint32_t RV32I_Type_I(string *inst);
    uint32_t RV32I_Type_S(string *inst);
    uint32_t RV32I_Type_B(string *inst);
    uint32_t RV32I_Type_U(string *inst);
    uint32_t RV32I_Type_J(string *inst);

public:
    uint32_t RV32I(string *inst);
};

#include "RVX_RV32I.cpp"

#endif // _RVX_RV32I_H_