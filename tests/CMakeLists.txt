
set(tests
    ctef_profile
)

foreach(test ${tests})
    add_executable(${test}_ctest ${test}_ctest.c)
    target_link_libraries(${test}_ctest PRIVATE ctef-profile)
endforeach()
