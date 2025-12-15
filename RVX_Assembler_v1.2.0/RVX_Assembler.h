#ifndef _RVX_ASSEMBLER_H_
#define _RVX_ASSEMBLER_H_

#include <stdint.h>
#include <string>
#include <fstream>
#include <string>
#include <iomanip>
#include "..\Lib\Map_Lib\Map.h"
#include "..\Lib\Hash_Lib\HashTable.h"
#include "..\Lib\Tool_Lib\Tool.h"
#include "RVX_Info.h"
using namespace std;

class RVX_Assembler
{
private:
    //当前指令（每次编译都是把一行先打包在此，不直接使用，其余函数容易调用）
    string inst[4];
    void loadInst(const string &line);
    //标签表(如：跳转用)
    HashTable<string, int> *labels;
    int collectLabels(const string &inputFile);

    //验证一行
    bool verifyInst();
    void loadLabels(int instAddr);

private:
    //编译一行RV32I指令集
    uint32_t RV32I();
public:
    RVX_Assembler();
    ~RVX_Assembler();
    //解释单行
    uint32_t interpret(const string &line);
    //编译文件
    int compile(const string &inputFile, const string &outputFile);
    //替换标签
    int replaceLabels(const string &inputFile, const string &outputFile, bool removeLabels = true);
    //验证文件
    int verify(const string &inputFile);
};

#include "RA_RV32I.cpp"
#include "RVX_Assembler_Pub.cpp"
#include "RVX_Assembler_Pri.cpp"

#endif // _RVX_ASSEMBLER_H_