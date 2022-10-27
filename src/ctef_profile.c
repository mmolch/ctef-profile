#include "ctef_profile.h"



/**************************************************************************************************
* CtefProbe
**************************************************************************************************/


struct CtefProbe
{
    char* name;
    long time_start;
    long time_end;
    long thread_id;
};

CtefProbe*
ctef_probe_new(void)
{

}

void
ctef_probe_delete(CtefProbe* probe)
{

}
