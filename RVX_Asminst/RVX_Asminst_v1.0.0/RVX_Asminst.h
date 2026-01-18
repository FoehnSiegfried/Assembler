#ifndef _RVX_ASMINST_H_
#define _RVX_ASMINST_H_

#include <cstdint>
using namespace std;

#include "../../Lib/TSOM_Tool_Lib/TSOM_Tool.h"
#include "../RVX_RVInst\RVX_RVInst_v1.0.0\RVX_Info.h"
#include "../RVX_RVInst\RVX_RVInst_v1.0.0\RV_Integer\RVX_RV32I.h"

#define RVX_ASMINST_VERSION "1.0.0"

// code数组大小
#define ASMINST_MAX_CODE_VOLUME 16

enum ASMINST_FORMAT
{
    AF_LI
};

enum ASMINST_PLACEFORMAT
{
    AP_INST_REG_NUM // 0指令 1寄存器 2数字
};

struct RVX_Asminst_Info
{
    int af; // 指令型
    int ap; // 指令结构型（分布位置如：op rd imm）
};

static Map<string, RVX_Asminst_Info> AsminstMap = {
    {"li", {AF_LI, AP_INST_REG_NUM}}};

class RVX_Asminst
{
private:
    RVX_RV32I rv32i;//处理RV32I指令集

private:
    int codeNum = 0;
    uint32_t code[ASMINST_MAX_CODE_VOLUME];

    void clearCode(); // 清空code和codeNum（全部置零）

    int findKeyRVInst(string &key);    // 查找是否存在"key"关键字(范围：RV)
    int verifyRVInstMap(string *inst); // 检测一条指令的结构是否合法(范围：RV)

private:                         // pseudo
    int pseudo_li(string *inst); // 加载32位立即数

public:
    int getCodeNum();                // 获取asminstNum
    uint32_t getCode(int codeIndex); // 获取asminst数组的asminstIndex位置上的指令（一般配合getAsminstNum使用）

    int findKey(string &key);     // 查找是否存在"key"关键字(范围：ASM RV)
    int verifyInst(string *inst); // 检测一条指令的结构是否合法(范围：ASM RV)
    int interpret(string *inst);
};

#include "RVX_Asminst_Pub.cpp"
#include "RVX_Asminst_Pri.cpp"
#include "RVX_Asminst_Pri_Pseudo.cpp"

#endif // _RVX_ASMINST_H_