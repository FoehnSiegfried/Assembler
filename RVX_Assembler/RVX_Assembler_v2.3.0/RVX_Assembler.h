#ifndef _RVX_ASSEMBLER_H_
#define _RVX_ASSEMBLER_H_

#include <cstdint>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

#include "..\..\Lib\Map_Lib\Map.h"
#include "..\..\Lib\Hash_Lib\HashTable.h"
#include "..\..\Lib\TSOM_Tool_Lib\TSOM_Tool.h"
#include "..\..\RVX_Asminst\RVX_Asminst_v1.0.0\RVX_Asminst.h"

#define RVX_ASSEMBLER_VERSION "2.3.0"

// 如果该参数被定义，则compile输出十六进制文本，否则为二进制数据
#define RVX_TEST_OUTPUT_HEX

// 指令容器inst大小
#define RVX_MAX_INSTVOLUNM 4
// 指令进位一次占用PC大小,PC一次进位的值(一般为+4,也就填4)
#define RVX_PC_ONCE_SIZE 4

#define RVX_INST_LABEL ".label"

enum RVXINST_FORMAT
{
    RF_LABEL
};

enum RVXINST_PLACEFORMAT
{
    RP_INST_NONUM // 0指令 1非数字
};

struct RVX_RVXInst_Info
{
    int rf; // 指令型
    int rp; // 指令结构型（分布位置如：inst nonum）
};

static Map<string, RVX_RVXInst_Info> RVXInstMap = {
    {RVX_INST_LABEL, {RF_LABEL, RP_INST_NONUM}}};

class RVX_Assembler
{
private:                             // 具体指令区
    RVX_Asminst asminst;             // 具体指令处理类
    string inst[RVX_MAX_INSTVOLUNM]; // 指令容器inst
    void clearInst();                // inst全部复位
    void loadInst(const string &line);

private:
    int findKey(string &key); // 全局查找是否有"key"关键字
    int verifyInst();//检测一条指令的结构是否合法(范围：RVX ASM RV)

private: // 编译器指令处理区
    //.label
    HashTable<string, int> labels; //  标签表Label
    int collectLabels(const string &inputFile);
    int loadLabels(int instIndex); // 给当前指令装填label，没有则不做操作（因此一般强制使用）

public:
    int getCodeNum();                // 获取asminstCodeNum
    uint32_t getCode(int codeIndex); // 获取asminstCode数组的asminstCodeIndex位置上的指令（一般配合getAsminstCodeNum使用）

    int interpret(const string &line);                              // 解释单行
    int compile(const string &inputFile, const string &outputFile); // 编译文件

    int replaceLabels(const string &inputFile, const string &outputFile, bool removeLabels = true); // 替换标签
    int verify(const string &inputFile);                                                            // 验证文件(检测所有指令的结构是否合法)
};

#include "RVX_Assembler_Pub.cpp"
#include "RVX_Assembler_Pri.cpp"

#endif // _RVX_ASSEMBLER_H_