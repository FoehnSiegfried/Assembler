/*
    TSOM_Tool.h
    TSOM Tool Library Header File
    Version: 2.1.0
    Author: TSOM-FoehnSiegfried
    Date: 2026-01-13
*/

#ifndef _TSOM_TOOL_H_
#define _TSOM_TOOL_H_

#include <string>
using namespace std;

#ifndef CONFIRM
#define CONFIRM 0
#endif // CONFIRM
#ifndef NEGATION
#define NEGATION -1
#endif // NEGATION

#define PLACEHOLDER_STRING "<TSOM&PLACEHOLDER&STRING>"

//输入字符串是整数就返回true（包括带符号的）
bool isSignedInteger(const string &str);

#include "TSOM_Tool.cpp"

#endif // _TSOM_TOOL_H_