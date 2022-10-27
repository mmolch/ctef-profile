#ifndef CTEF_PROFILE_H
#define CTEF_PROFILE_H


/** Private ******************************************************************/


typedef struct CtefProbe CtefProbe;

CtefProbe* __ctef_probe_new(const char* name);
void __ctef_probe_delete(CtefProbe* probe);

void __ctef_profile_begin(const char* filename);
void __ctef_profile_end();


/** Macros *******************************************************************/


#define CTEF_PROFILE 1
#if CTEF_PROFILE 1

    /**
     * @brief Start a new profiling session, writing the json data into the
     *        file specified by filename
    */
    #define CTEF_PROFILE_BEGIN(filename)

    /**
     * @brief End the profiling session
    */
    #define CTEF_PROFILE_END()

    #define CTEF_PROFILE_BEGIN_SECTION(variable, name)
    #define CTEF_PROFILE_END_SECTION(variable)

    #define CTEF_PROFILE_BEGIN_FUNCTION()
    #define CTEF_PROFILE_END_FUNCTION()

#else // CTEF_PROFILE

    #define CTEF_PROFILE_BEGIN(filename)
    #define CTEF_PROFILE_END()

    #define CTEF_PROFILE_BEGIN_SECTION(variable, name)
    #define CTEF_PROFILE_END_SECTION(variable)

    #define CTEF_PROFILE_BEGIN_FUNCTION()
    #define CTEF_PROFILE_END_FUNCTION()

#endif // CTEF_PROFILE


#endif // CTEF_PROFILE_H
