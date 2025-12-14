#ifndef _TOOL_CPP_
#define _TOOL_CPP_

#include "Tool.h"

bool isSignedInteger(const string &str)
{
    if (str.empty())
        return false;
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+')
    {
        start = 1;
        if (str.length() == 1)
            return false;
    }
    for (size_t i = start; i < str.length(); i++)
    {
        if (!isdigit(static_cast<unsigned char>(str[i])))
        {
            return false;
        }
    }
    return true;
}

#endif // _TOOL_CPP_