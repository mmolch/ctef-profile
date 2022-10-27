#include "ctef_profile.h"

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct CtefProfiler CtefProfiler;
static CtefProfiler* active_profiler = NULL;
void ctef_profiler_write_probe(CtefProfiler* profiler, const CtefProfilerProbe* probe);


/**************************************************************************************************
* Helpers
**************************************************************************************************/


static long
get_time_in_microseconds()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return 1e6 * now.tv_sec + now.tv_nsec * 1e-3;
}


/**************************************************************************************************
* CtefProfilerProbe
**************************************************************************************************/


struct CtefProfilerProbe
{
    char* name;
    long time_start;
    long time_stop;
    long thread_id;
};


static CtefProfilerProbe*
ctef_profiler_probe_new(const char* name)
{
    CtefProfilerProbe* probe = malloc(sizeof(CtefProfilerProbe));
    assert(probe != NULL);

    {
        int name_length = strlen(name);
        probe->name = malloc(name_length+1);
        assert(probe->name != NULL);
        memcpy(probe->name, name, name_length);
        probe->name[name_length] = '\0';
    }

    return probe;
}


static void
ctef_profiler_probe_delete(CtefProfilerProbe* probe)
{
    free(probe->name);
    free(probe);
    probe = NULL;
}


static void
ctef_profiler_probe_start(CtefProfilerProbe* probe)
{
    probe->time_start = get_time_in_microseconds();
}


static void
ctef_profiler_probe_stop(CtefProfilerProbe* probe)
{
    probe->time_stop = get_time_in_microseconds();
}


CtefProfilerProbe*
ctef_profiler_probe_begin(const char* name)
{
    assert(name != NULL);

    CtefProfilerProbe* probe = ctef_profiler_probe_new(name);

    probe->thread_id = pthread_self();
    ctef_profiler_probe_start(probe);

    return probe;
}


void
ctef_profiler_probe_end(CtefProfilerProbe* probe)
{
    assert(probe != NULL);

    ctef_profiler_probe_stop(probe);

    ctef_profiler_write_probe(active_profiler, probe);

    ctef_profiler_probe_delete(probe);
}


/**************************************************************************************************
* CtefProfiler
**************************************************************************************************/


struct CtefProfiler
{
    FILE* fd;
    pthread_mutex_t lock;
};


static CtefProfiler*
ctef_profiler_new(const char* filename)
{
    CtefProfiler* profiler = malloc(sizeof(CtefProfiler));

    profiler->fd = fopen(filename, "w");
    assert(profiler->fd != NULL);

    assert(pthread_mutex_init(&profiler->lock, NULL) == 0);

    static const char header[] = "{\"otherData\": {},\"traceEvents\":[{}";
    fwrite(header, sizeof(header)-1, 1, profiler->fd);
    fflush(profiler->fd);

    return profiler;
}


static void
ctef_profiler_delete(CtefProfiler* profiler)
{
    if (profiler->fd != NULL)
    {
        static const char footer[] = "]}";
        fwrite(footer, sizeof(footer)-1, 1, profiler->fd);

        fclose(profiler->fd);
    }

    free(profiler);
}


void
ctef_profiler_write_probe(CtefProfiler* profiler, const CtefProfilerProbe* probe)
{
    long duration = probe->time_stop - probe->time_start;

    const char json_template[] = ",{"
                                 "\"cat\":\"function\","
                                 "\"dur\":%ld,"
                                 "\"name\":\"%s\","
                                 "\"ph\":\"X\","
                                 "\"pid\":0,"
                                 "\"tid\":%lu,"
                                 "\"ts\":%ld"
                                 "}";

    int json_length = snprintf(NULL, 0, json_template, duration,
                                                       probe->name,
                                                       probe->thread_id,
                                                       probe->time_start);

    char buffer[json_length+1];
    snprintf(buffer, json_length+1, json_template, duration,
                                                   probe->name,
                                                   probe->thread_id,
                                                   probe->time_stop);

    pthread_mutex_lock(&profiler->lock);
    fwrite(buffer, json_length, 1, profiler->fd);
    fflush(profiler->fd);
    pthread_mutex_unlock(&profiler->lock);

}


/**************************************************************************************************
* ctef_profile_begin / ctef_profile_end
**************************************************************************************************/


void
ctef_profile_begin(const char* filename)
{
    assert(active_profiler == NULL);

    active_profiler = ctef_profiler_new(filename);
}


void
ctef_profile_end()
{
    assert(active_profiler != NULL);

    ctef_profiler_delete(active_profiler);
}
