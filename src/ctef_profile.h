#ifndef CTEF_PROFILE_H
#define CTEF_PROFILE_H


#define CTEF_PROFILE 1
#ifdef CTEF_PROFILE
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

    
    /** Private **************************************************************/


    typedef struct CtefProbe CtefProbe;

    // Don't use. Use the macros CTEF_PROFILE_BEGIN_SECTION() or
    // CTEF_PROFILE_BEGIN_FUNCTION() instead
    CtefProbe* ctef_probe_begin(const char* name);

    // Don't use. Use the macros CTEF_PROFILE_END_SECTION() or
    // CTEF_PROFILE_END_FUNCTION() instead
    void ctef_probe_end(CtefProbe* probe);

    // Don't use. Use the macro CTEF_PROFILE_BEGIN() instead
    void ctef_profile_begin(const char* filename);
    
    // Don't use. Use the macro CTEF_PROFILE_END() instead
    void ctef_profile_end();

#else // CTEF_PROFILE

    #define CTEF_PROFILE_BEGIN(filename)
    #define CTEF_PROFILE_END()

    #define CTEF_PROFILE_BEGIN_SECTION(variable, name)
    #define CTEF_PROFILE_END_SECTION(variable)

    #define CTEF_PROFILE_BEGIN_FUNCTION()
    #define CTEF_PROFILE_END_FUNCTION()

#endif // CTEF_PROFILE


#endif // CTEF_PROFILE_H
