#ifndef _RVX_PSEUDOINST_H_
#define _RVX_PSEUDOINST_H_

#include <cstdint>
#include <string>
using namespace std;

#include "..\Lib\Map_Lib\Map.h"
#include "..\Lib\TSOM_Tool_Lib\TSOM_Tool.h"

#include "..\RealInst\RVInstGather\RVInst.h"

#define PI_CODE_VOLUME 16

enum PseudoInst_Inst
{
    PII_LI = 0
};

enum PseudoInst_Format
{
    PIF_INST_REG_IMM = 0
};

struct PseudoInst_Info
{
    int inst;
    int fomart;
};

static Map<string, PseudoInst_Info> PIMap = {
    {"li", {PII_LI, PIF_INST_REG_IMM}}
};

class PseudoInst
{
private:
    int PICodeNum = 0;
    string PICode[PI_CODE_VOLUME];
    void clearPICode();

private:
    int PI_li(string *ptr_inst);
public:
    int getPICodeNum();
    string getPICode(int PICodeIndex);
    
    int searchKeyWord(string &val_keyWord);
    int verify(string *ptr_inst);
    int interpret(string *ptr_inst);
};

#include "PseudoInst_Pri.cpp"
#include "PseudoInst_Pub.cpp"

#endif // _RVX_PSEUDOINST_H_