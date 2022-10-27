#define CTEF_PROFILE 1 // Enable profiling
#include <ctef_profile.h>

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *thread_func(void *arg)
{
    CTEF_PROFILE_BEGIN_FUNCTION();

    usleep(500000);

    CTEF_PROFILE_END_FUNCTION();
    return NULL;
}


void do_something(void)
{
    CTEF_PROFILE_BEGIN_FUNCTION();

    usleep(100000);

    CTEF_PROFILE_END_FUNCTION();
}

int main( int argc, char* argv[] )
{
    CTEF_PROFILE_BEGIN("profile.json");

    CTEF_PROFILE_BEGIN_SECTION(startup_probe, "Startup");

    do_something();

    pthread_t t1, t2;
    int i = 1;
    int j = 2;

    pthread_create(&t1, NULL, &thread_func, &i);
    pthread_create(&t2, NULL, &thread_func, &j);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    CTEF_PROFILE_END_SECTION(startup_probe);

    CTEF_PROFILE_BEGIN_SECTION(shutdown_probe, "Shutdown");

    do_something();

    CTEF_PROFILE_END_SECTION(shutdown_probe);

    CTEF_PROFILE_END();
    return 0;
}
