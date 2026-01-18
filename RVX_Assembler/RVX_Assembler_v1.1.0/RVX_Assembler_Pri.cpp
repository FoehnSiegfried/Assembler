#ifndef _RVX_ASSEMBLER_PRI_CPP_
#define _RVX_ASSEMBLER_PRI_CPP_

#include "RVX_Assembler.h"

string *RVX_Assembler::splitLine(const string &vals)
{
    int index = 0;
    string *line = new string[4];
    string buf;
    for (int i = 0; i < vals.length(); i++)
    {
        if (vals[i] == ' ')
        {
            line[index] = buf;
            buf = "";
            index++;
            if (index >= 4)
                break;
        }
        else
        {
            buf += vals[i];
        }
    }
    if (index < 4)
        line[index] = buf;
    return line;
}
HashTable<string, int>* RVX_Assembler::collectLabels(const string &inputFile)
{
    ifstream inputStream;
    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }

    HashTable<string, int> *labels = new HashTable<string, int>(101);

    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        string *vals = splitLine(lineBuf);
        if (vals[0] == TAG_LABEL)
        {
            labels->insert(vals[1], index);
            delete[] vals;
            continue;
        }
        index++;
        delete[] vals;
    }

    // Add code here to read from inputStream and collect labels
    inputStream.close();
    return labels;
}

bool RVX_Assembler::verifyLine(string *vals)
{
    int type = RV32IMap[vals[0]].instFormat;
    switch (type)
    {
    case TYPE_R:
        if (!((regMap.find(vals[1])) && (regMap.find(vals[2])) && (regMap.find(vals[3]))))
            return false;
        break;
    case TYPE_I:
        if (!((regMap.find(vals[1])) && (regMap.find(vals[2])) && (isSignedInteger(vals[3]))))
            return false;
        break;
    case TYPE_S:
        if (!((regMap.find(vals[1])) && (isSignedInteger(vals[2])) && (regMap.find(vals[3]))))
            return false;
        break;
    case TYPE_B:
        if (!((regMap.find(vals[1])) && (regMap.find(vals[2])) && (isSignedInteger(vals[3]))))
            return false;
        break;
    case TYPE_U:
        if (!((regMap.find(vals[1])) && (isSignedInteger(vals[2]))))
            return false;
        break;
    case TYPE_J:
        if (!((regMap.find(vals[1])) && (isSignedInteger(vals[2]))))
            return false;
        break;
    default:
        return false;
    }
    return true;
}

int RVX_Assembler::preprocessLabel(const string &inputFile, const string &outputFile)
{
    ifstream inputStream;
    ofstream outputStream;

    inputStream.open(inputFile, ios::in);
    if (!inputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }
    outputStream.open(outputFile, ios::out | ios::trunc); //| ios::binary
    if (!outputStream.is_open())
    {
        throw runtime_error("File can't be opened.");
    }

    HashTable<string, int>* labels = collectLabels(inputFile);

    int index = 1;
    string lineBuf;
    while (getline(inputStream, lineBuf))
    {
        string *vals = splitLine(lineBuf);
        if (vals[0] == TAG_LABEL)
        {
            continue;
        }
        else if (RV32IMap[vals[0]].instFormat == TYPE_I && labels->ownKey(vals[3]))
        {
            int labelAddr = labels->search(vals[3]);
            outputStream << vals[0] << " " << vals[1] << " " << vals[2] << " " << to_string(4 * (labelAddr - index)) << endl;
        }
        else if (RV32IMap[vals[0]].instFormat == TYPE_B && labels->ownKey(vals[3]))
        {
            int labelAddr = labels->search(vals[3]);
            outputStream << vals[0] << " " << vals[1] << " " << vals[2] << " " << to_string(4 * (labelAddr - index)) << endl;
        }
        else if (RV32IMap[vals[0]].instFormat == TYPE_J && labels->ownKey(vals[2]))
        {
            int labelAddr = labels->search(vals[2]);
            outputStream << vals[0] << " " << vals[1] << " " << to_string(4 * (labelAddr - index)) << endl;
        }
        else
        {
            outputStream << lineBuf << endl;
        }
        delete[] vals;
        index++;
    }

    delete labels;
    inputStream.close();
    outputStream.close();
    return SUCCESS;
}

#endif // _RVX_ASSEMBLER_PRI_CPP_