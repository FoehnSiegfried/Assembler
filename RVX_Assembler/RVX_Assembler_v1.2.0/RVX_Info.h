#ifndef _RVX_INFO_H_
#define _RVX_INFO_H_

#include <string>
#include <stdint.h>
#include "..\Lib\Map_Lib\Map.h"
using namespace std;

#define TAG_LABEL "label"

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



#endif // _RVX_INFO_H_