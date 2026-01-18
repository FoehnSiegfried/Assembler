#ifndef _RVXASSEMBLER_H_
#define _RVXASSEMBLER_H_

#include <fstream>
#include <string>
#include <iomanip>
#include <stdint.h>
#include "..\Lib\Map_Lib\Map.h"
#include "RVXInformation.h"
using namespace std;

// Compile return
#define SUCESS 0   // sucess
#define OPENERR -1 // file cant be open

class RVXAssembler
{
private:
    string *instLoad(string &val);
    uint32_t takeRV32ITypeR(string *inst);
    uint32_t takeRV32ITypeI(string *inst);
    uint32_t takeRV32ITypeS(string *inst);
    uint32_t takeRV32ITypeB(string *inst);
    uint32_t takeRV32ITypeU(string *inst);
    uint32_t takeRV32ITypeJ(string *inst);
    uint32_t instCompileSelect(string *inst);

    // use unit
    bool checkInst(string *inst);
    bool isSignedInteger(const string &str);

public:
    uint32_t Compile(string *inst);
    int Compile(string input, string output);
};

#include "RVXAssembler_Pri.cpp"
#include "RVXAssembler_Pub.cpp"

#endif