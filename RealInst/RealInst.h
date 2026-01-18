#ifndef _RVX_REALINST_H_
#define _RVX_REALINST_H_

#include <string>
#include <stdint.h>
using namespace std;

#include "..\Lib\Map_Lib\Map.h"
#include "..\Lib\TSOM_Tool_Lib\TSOM_Tool.h"

#include ".\RVInstGather\RVInst.h"
#include ".\RVInstGather\RV32I\RV32I.h"

class RealInst
{
private:
    RV32I rv32i;
    private:
    int searchRVInstFormat(string val_instName);
public:
    int searchKeyWord(string &val_keyWord);
    int verify(string *ptr_inst);
    uint32_t interpret(string *ptr_inst);
};

#include "RealInst.cpp"

#endif // _REALINST_H_