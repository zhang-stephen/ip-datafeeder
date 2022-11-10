# Options for cmake

option(
    PLATFORM_WINDOWS
    "indicates if the host is Windows"
    ${CMAKE_HOST_WIN32}
)

if(CMAKE_HOST_WIN32)
    set(PLATFORM_WINDOWS true)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# EOF