#ifndef CTEF_PROFILE_H
#define CTEF_PROFILE_H


/**************************************************************************************************
* Macros
**************************************************************************************************/


#ifdef CTEF_PROFILE

	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define CTEF_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define CTEF_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define CTEF_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define CTEF_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define CTEF_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define CTEF_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define CTEF_FUNC_SIG __func__
	#else
		#define CTEF_FUNC_SIG "CTEF_FUNC_SIG unknown!"
	#endif

    /**
     * @brief Start a new profiling session, writing the json data into the
     *        file specified by filename
    */
    #define CTEF_PROFILE_BEGIN(filename) ctef_profile_begin(filename)

    /**
     * @brief End the profiling session
    */
    #define CTEF_PROFILE_END() ctef_profile_end()

    /**
     * @brief Begin a profiling section. Use CTEF_PROFILE_END_SECTION()
     *        to end the section
    */
    #define CTEF_PROFILE_BEGIN_SECTION(variable, name) CtefProfilerProbe* variable = ctef_profiler_probe_begin(name)

    /**
     * @brief End a profiling section. Provide the variable you
     *        gave to CTEF_PROFILE_BEGIN_SECTION()
    */
    #define CTEF_PROFILE_END_SECTION(variable) ctef_profiler_probe_end(variable)

    /**
     * @brief Begin a profiling section with the function name as name
     *        and an automatically generated variable name
    */
    #define CTEF_PROFILE_BEGIN_FUNCTION() CtefProfilerProbe* ctef##CTEF_FUNC_SIG = ctef_profiler_probe_begin(CTEF_FUNC_SIG)

    /**
     * @brief Ends profiling section started with CTEF_PROFILE_BEGIN_FUNCTION()
    */
    #define CTEF_PROFILE_END_FUNCTION() ctef_profiler_probe_end(ctef##CTEF_FUNC_SIG)

    
#else // CTEF_PROFILE

    #define CTEF_PROFILE_BEGIN(filename)
    #define CTEF_PROFILE_END()

    #define CTEF_PROFILE_BEGIN_SECTION(variable, name)
    #define CTEF_PROFILE_END_SECTION(variable)

    #define CTEF_PROFILE_BEGIN_FUNCTION()
    #define CTEF_PROFILE_END_FUNCTION()

#endif // CTEF_PROFILE


/**************************************************************************************************
* Private
**************************************************************************************************/


typedef struct CtefProfilerProbe CtefProfilerProbe;

// Don't use. Use the macros CTEF_PROFILE_BEGIN_SECTION() or
// CTEF_PROFILE_BEGIN_FUNCTION() instead
CtefProfilerProbe* ctef_profiler_probe_begin(const char* name);

// Don't use. Use the macros CTEF_PROFILE_END_SECTION() or
// CTEF_PROFILE_END_FUNCTION() instead
void ctef_profiler_probe_end(CtefProfilerProbe* probe);

// Don't use. Use the macro CTEF_PROFILE_BEGIN() instead
void ctef_profile_begin(const char* filename);

// Don't use. Use the macro CTEF_PROFILE_END() instead
void ctef_profile_end();


#endif // CTEF_PROFILE_H
