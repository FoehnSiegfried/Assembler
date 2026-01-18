#ifndef _RVX_ASSEMBLER_H_
#define _RVX_ASSEMBLER_H_

#include <string>
#include <cstdint>
#include <fstream>
#include <iomanip>
using namespace std;

#include "..\..\Lib\Map_Lib\Map.h"
#include "..\..\Lib\Hash_Lib\HashTable.h"
#include "..\..\Lib\TSOM_Tool_Lib\TSOM_Tool.h"

#include "..\..\RealInst\RealInst.h"
#include "..\..\PseudoInst\PseudoInst.h"

#define RVX_ASSEMBLER_VERSION "3.0.0"

#define RVX_TEMP_LABEL "/temp_loadLabel"
#define RVX_INSTVOLUME 16

#define ASM_INST_LABEL ".label"

enum AsmInst_Inst
{
    AII_LABEL = 0
};

enum AsmInst_Format
{
    AIF_INST_STR = 0
};

struct AsmInst_Info
{
    int inst;
    int format;
};

static Map<string, AsmInst_Info> AIMap = {
    {ASM_INST_LABEL, {AII_LABEL, AIF_INST_STR}}};

class RVX_Assembler
{
private:
    string temp;

    RealInst ri;
    PseudoInst pi;

    string inst[RVX_INSTVOLUME];
    void initInst();
    void valSetInst(string &val_instLine);

    int searchKeyWord(string &val_keyWord);
public:
    RVX_Assembler(string &val_temp);

    int loadLabel(string &val_input, string &val_output);
    int verify(string &val_input);
    int compile(string &val_input, string &val_output);
};

#include "RVX_Assembler_Pri.cpp"
#include "RVX_Assembler_Pub.cpp"

#endif // _RVX_ASSEMBLER_H_