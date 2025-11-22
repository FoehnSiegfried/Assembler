#ifndef _RVXINFORMATION_H_
#define _RVXINFORMATION_H_

#include <string>
#include <stdint.h>
#include "..\Lib\Map_Lib\Map.h"
using namespace std;

/*
R
inst rd rs1 rs2
add x10 x11 x12
I
inst rd rs1 imm
addi x10 x11 0
S
inst rs2 imm rs1
sb x11 8 x10
B
inst rs1 rs2 imm
bne x10 x11 8
U
inst rd imm
lui x10 128
J
inst rd imm
jal x10 128
*/

enum INST_FORMAT
{
    TYPE_R,
    TYPE_I,
    TYPE_S,
    TYPE_B,
    TYPE_U,
    TYPE_J
};

struct RVInst
{
    string instName;
    short instFormat;
    uint32_t opcode;
    uint32_t funct3;
    uint32_t funct7;
};

static Map<string, uint32_t> regMap = {
    {"x0", 0},
    {"x1", 1},
    {"x2", 2},
    {"x3", 3},
    {"x4", 4},
    {"x5", 5},
    {"x6", 6},
    {"x7", 7},
    {"x8", 8},
    {"x9", 9},
    {"x10", 10},
    {"x11", 11},
    {"x12", 12},
    {"x13", 13},
    {"x14", 14},
    {"x15", 15},
    {"x16", 16},
    {"x17", 17},
    {"x18", 18},
    {"x19", 19},
    {"x20", 20},
    {"x21", 21},
    {"x22", 22},
    {"x23", 23},
    {"x24", 24},
    {"x25", 25},
    {"x26", 26},
    {"x27", 27},
    {"x28", 28},
    {"x29", 29},
    {"x30", 30},
    {"x31", 31},
};

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

#endif