cmake_minimum_required(VERSION 3.0)
project(ctef-profile
        VERSION 1.0.0
        LANGUAGES C
)

set(CMAKE_C_STANDARD 99)

add_library(ctef-profile STATIC
    src/ctef_profile.c
)
