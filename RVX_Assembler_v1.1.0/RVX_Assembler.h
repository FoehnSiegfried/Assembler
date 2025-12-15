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

#define SUCCESS 0 // success

class RVX_Assembler
{
private:
    string *splitLine(const string &line);
    HashTable<string, int> *collectLabels(const string &inputFile);
    bool verifyLine(string *vals);
    int preprocessLabel(const string &inputFile, const string &outputFile);

    uint32_t RV32I(string *inst);
    string cache;

public:
    RVX_Assembler(const string &cache);
    ~RVX_Assembler();

    uint32_t lineCompile(const string &line);                                // 编译一行指令
    int fileCompile(const string &inputFile, const string &outputFile);      // 编译文件
    int fileCompile_Word(const string &inputFile, const string &outputFile); // 编译文件

    int verify(const string &inputFile);                                  // 验证
    int preprocessing(const string &inputFile, const string &outputFile); // 预处理
};

#include "RA_RV32I.cpp"
#include "RVX_Assembler_Pub.cpp"
#include "RVX_Assembler_Pri.cpp"

#endif // _RVX_ASSEMBLER_H_