cmake_minimum_required(VERSION 3.0)
project(ctef-profile
        VERSION 1.0.0
        LANGUAGES C
)

set(CMAKE_C_STANDARD 99)

add_library(ctef-profile STATIC
    src/ctef_profile.c
)

target_link_libraries(ctef-profile PUBLIC
    pthread
    rt
)

target_include_directories(ctef-profile PUBLIC
    src
)

if(CMAKE_CURRENT_LIST_DIR STREQUAL ${CMAKE_SOURCE_DIR})
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()
