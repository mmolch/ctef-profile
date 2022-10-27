#define CTEF_PROFILE 1 // Enable profiling
#include <ctef_profile.h>

void do_something(void)
{
    CTEF_PROFILE_BEGIN_FUNCTION();

    /* Some code */

    CTEF_PROFILE_END_FUNCTION();
}

int main( int argc, char* argv[] )
{
    CTEF_PROFILE_BEGIN("profile.json");

    CTEF_PROFILE_BEGIN_SECTION(startup_probe, "Startup");

    /* some code */

    do_something();

    /* more code */

    CTEF_PROFILE_END_SECTION(startup_probe);

    do_something();

    CTEF_PROFILE_END();
    return 0;
}
