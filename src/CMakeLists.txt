# release source file building
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_subdirectory(common)
add_subdirectory(json)
add_subdirectory(logger)
add_subdirectory(stream)
add_subdirectory(utility)

set(IPDF_EXECUTABLE_BIN ipdf)

add_executable(${IPDF_EXECUTABLE_BIN})

target_sources(
    ${IPDF_EXECUTABLE_BIN}
    PRIVATE
        main.cc
)

target_link_libraries(
    ${IPDF_EXECUTABLE_BIN}
    PUBLIC
        compiler
        common
        json
        logger
        stream
        utility
)

# EOF
