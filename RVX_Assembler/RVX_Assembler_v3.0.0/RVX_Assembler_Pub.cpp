#ifndef _RVX_ASSEMBLER_PUB_CPP_
#define _RVX_ASSEMBLER_PUB_CPP_

#include "RVX_Assembler.h"

int RVX_Assembler::loadLabel(string &val_input, string &val_output)
{
    ifstream inputStream;
    ofstream outputStream;
    inputStream.open(val_input, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");
    outputStream.open(val_output, ios::out | ios::trunc); // | ios::binary
    if (!outputStream.is_open())
        throw runtime_error("File can't be opened.");

    HashTable<string, int> labels;
    int instIndex = 1;
    int lineNum = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        valSetInst(lineBuf);
        lineNum++;
        if (inst[0] == ASM_INST_LABEL)
        {
            if ((!isSignedInteger(inst[1])) && (!labels.ownKey(inst[1])))
            {
                labels.insert(inst[1], instIndex * 4);

                continue;
            }
            else
                return lineNum - 1;
        }
        instIndex++;
    }
    inputStream.clear();
    inputStream.seekg(0, ios::beg);

    instIndex = 1;
    lineBuf = "";
    while (getline(inputStream, lineBuf))
    {
        valSetInst(lineBuf);
        if (inst[0] != ASM_INST_LABEL)
        {
            for (int i = 0; ((i < RVX_INSTVOLUME) && (inst[i] != PLACEHOLDER_STRING)); i++)
            {
                //
                if (inst[i] == "err")
                {
                    cout << instIndex << endl;
                    cout << labels.search("err") << endl;
                }
                //
                if (((searchKeyWord(inst[i]) != CONFIRM) && (!isSignedInteger(inst[i])) && labels.ownKey(inst[i])))
                    inst[i] = to_string((labels.search(inst[i]) - (instIndex * 4)));
                outputStream << inst[i];
                if (inst[i + 1] != PLACEHOLDER_STRING)
                    outputStream << ' ';
            }
            outputStream << '\n';
            instIndex++;
        }
    }
    inputStream.close();
    outputStream.close();

    return CONFIRM;
}

int RVX_Assembler::verify(string &val_input)
{
    string temp_label = RVX_TEMP_LABEL;
    int loadLabelInfo = loadLabel(val_input, temp_label);
    if (loadLabelInfo != CONFIRM)
        return loadLabelInfo;

    ifstream inputStream;
    inputStream.open(temp_label, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");

    int lineNum = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        valSetInst(lineBuf);
        lineNum++;
        if (ri.verify(inst) == CONFIRM)
            continue;
        if (pi.verify(inst) == CONFIRM)
            continue;
        if (AIMap.find(inst[0]))
        {
            switch (AIMap[inst[0]].format)
            {
            case AIF_INST_STR:
                if ((inst[0] == PLACEHOLDER_STRING) || (inst[1] == PLACEHOLDER_STRING))
                    return lineNum - 1;
                if (!AIMap.find(inst[0]))
                    return lineNum - 1;
                if (isSignedInteger(inst[1]))
                    return lineNum - 1;
                continue;
            default:
                return lineNum - 1;
            }
        }
        return lineNum - 1;
    }

    inputStream.close();
    return CONFIRM;
}

int RVX_Assembler::compile(string &val_input, string &val_output)
{
    int verifyInfo = verify(val_input);
    if (verifyInfo != CONFIRM)
        return verifyInfo;

    string temp_label = RVX_TEMP_LABEL;
    ifstream inputStream;
    ofstream outputStream;
    inputStream.open(temp_label, ios::in);
    if (!inputStream.is_open())
        throw runtime_error("File can't be opened.");
    outputStream.open(val_output, ios::out | ios::trunc); // | ios::binary
    if (!outputStream.is_open())
        throw runtime_error("File can't be opened.");

    int lineNum = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        valSetInst(lineBuf);
        lineNum++;
        if (ri.verify(inst) == CONFIRM)
        {
            uint32_t code = ri.interpret(inst);
            if (code == RVX_ERROR_INST)
                return lineNum - 1;
            outputStream << hex << setw(8) << setfill('0') << code << '\n';
            continue;
        }
        if (pi.verify(inst) == CONFIRM)
        {
            int piInterpretInfo = pi.interpret(inst);
            if (piInterpretInfo != CONFIRM)
                return lineNum - 1;
            for (int i = 0; i < pi.getPICodeNum(); i++)
            {
                string piCode = pi.getPICode(i);
                valSetInst(piCode);
                if (ri.verify(inst) == CONFIRM)
                {
                    uint32_t code = ri.interpret(inst);
                    if (code == RVX_ERROR_INST)
                        return lineNum - 1;
                    outputStream << hex << setw(8) << setfill('0') << code << '\n';
                }
                else
                {
                    return lineNum - 1;
                }
            }
            continue;
        }
        if (AIMap.find(inst[0]))
        {
            int aiInst = AIMap[inst[0]].inst;
            switch (aiInst)
            {
            case AII_LABEL:
                continue;
            default:
                return lineNum - 1;
            }
        }
        return lineNum - 1;
    }

    inputStream.close();
    outputStream.close();
    return CONFIRM;
}

#endif // _RVX_ASSEMBLER_PUB_CPP_