#ifndef _RVX_ASMINST_H_
#define _RVX_ASMINST_H_

#include <cstdint>
using namespace std;

#include "../Lib/Tool_Lib/Tool.h"
#include "../RVX_Asminst/RVX_RVInst/RVX_Info.h"
#include "../RVX_Asminst/RVX_RVInst/RVX_RV32I.h"

#define RVX_ASMINST_VERSION "2.1.0"

//asminst数组大小
#define MAX_ASMINST_VOLUME 16

enum ASMINST_FORMAT{
    AF_LI
};

enum ASMINST_PLACE_FORMAT{
    AFP_OP_RD_IMM
};

struct RVX_AsminstInfo
{
    //指令型
    int af;
    //指令结构型（分布位置如：op rd imm）
    int afp;
};

static Map<string, RVX_AsminstInfo> AsminstMap = {
    {"li", {AF_LI, AFP_OP_RD_IMM}}
};

class RVX_Asminst{
private:
    RVX_RV32I rv32i;
private:
    int asminstNum = 0;
    uint32_t asminst[MAX_ASMINST_VOLUME];
    //清空asminst和asminstNum（全部置零）
    void clearAsminst();//
private:
    int pseudo_li(string* inst);
public:
    //获取asminstNum
    int getAsminstNum();//
    //获取asminst数组的asminstIndex位置上的指令（一般配合getAsminstNum使用）
    uint32_t getAsminst(int asminstIndex);//
    int findKey(string &key);//
    int verifyInst(string* inst);
    int RVX_Asm(string* inst);//
};

#include "RVX_Asminst_Pub.cpp"
#include "RVX_Asminst_Pri.cpp"
#include "RVX_Asminst_Pri_Pseudo.cpp"

#endif // _RVX_ASMINST_H_