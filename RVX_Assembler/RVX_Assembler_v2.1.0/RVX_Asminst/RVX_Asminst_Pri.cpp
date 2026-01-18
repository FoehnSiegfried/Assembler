#ifndef _RVX_ASMINST_PRI_CPP_
#define _RVX_ASMINST_PRI_CPP_

#include "RVX_Asminst.h"

#define RVX_ASMINST_PRI_VERSION "2.1.0"

void RVX_Asminst::clearAsminst()
{
    asminstNum = 0;
    for (int i = 0; i < MAX_ASMINST_VOLUME; i++)
    {
        asminst[i] = 0;
    }
}

#endif // _RVX_ASMINST_PRI_CPP_