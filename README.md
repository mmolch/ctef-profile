# Chrome Trace Event Format Profiler for C / C++ (CTEF Profiler)

A simple one-file (well, with header two-files) library written in C99 that lets you profile your C / C++ application visually by writing the trace into a json file in the trace event format used by Chrome / Chromium. This file can then be opened with Chrome's built-in tracing application (url: chrome://tracing)


## Audience
This library is intended for small-scale projects mainly written in C. While it obviously also works in C++, there are probably better alternatives for pure C++ (primarily because you don't have to manually mark the end of a function / scope / program).


## Usage
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

First you have to call `CTEF_PROFILE_BEGIN("some-file.json")` before calling any of the other CTEF_ macros. It has to be paired with a call to `CTEF_PROFILE_END()` when your application exits. \
The macro `CTEF_PROFILE_BEGIN_SECTION(variable, "section-name")` lets you create a section with a variable and name of your choice. It creates a probe which later has to be proceses with `CTEF_PROFILE_END_SECTION(variable)`. \
You can use `CTEF_PROFILE_BEGIN_FUNCTION()` and `CTEF_PROFILE_END_FUNCTION()` to mark a function. It will create a probe with the function's name and variable based on the function's name.


## Appendix
Trace event format (duration events): https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/edit#heading=h.nso4gcezn7n1
