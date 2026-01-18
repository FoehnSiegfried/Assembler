#ifndef _RVX_ASSEMBLER_H_
#define _RVX_ASSEMBLER_H_

#include <cstdint>
using namespace std;

#include <string>
#include <fstream>

#include "..\Lib\Map_Lib\Map.h"
#include "..\Lib\Hash_Lib\HashTable.h"
#include "..\Lib\Tool_Lib\Tool.h"
#include "../RVX_Assembler_v2.1.0/RVX_Asminst/RVX_Asminst.h"

#define RVX_ASSEMBLER_VERSION "2.1.0"

// 指令容器inst大小
#define MAX_RVXINST_VOLUNM 4
//指令进位一次占用PC大小,PC一次进位的值(一般为+4,也就填4)
#define PC_ONCE_SIZE 4

//-----------------RVXINST-----------------

#define RVXINST_LABEL ".label"

enum RVXINST_FORMAT
{
    RF_LABEL
};

static Map<string, int> RVXinstMap = {
    {RVXINST_LABEL, RF_LABEL}};

//-----------------RVXINST-----------------

class RVX_Assembler
{
private: // 具体指令区
    // 具体指令处理类
    RVX_Asminst asminst;
    // 当前指令索引位置
    int curinstIndex;
    // 指令容器inst
    string curinst[MAX_RVXINST_VOLUNM];
    void loadInst(const string &line); //

private: // 编译器指令处理区
    // Label:
    //  标签表Label
    HashTable<string, int> labels;
    int collectLabels(const string &inputFile); //
    // 给当前指令装填label，没有则不做操作（因此一般强制使用）
    int loadLabels();//

public:
    //获取asminstNum
    int getAsminstNum();//
    //获取asminst数组的asminstIndex位置上的指令（一般配合getAsminstNum使用）
    uint32_t getAsminst(int asminstIndex);//
    // 解释单行
    int interpret(const string &line);//
    // 编译文件
    int compile(const string &inputFile, const string &outputFile);

    // 替换标签
    int replaceLabels(const string &inputFile, const string &outputFile, bool removeLabels = true);

    // 验证文件
    int verify(const string &inputFile);//
};

#include "RVX_Assembler_Pub.cpp"
#include "RVX_Assembler_Pri.cpp"

#endif // _RVX_ASSEMBLER_H_