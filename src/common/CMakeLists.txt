# Common Lib for ip-Datafeeder
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_subdirectory(stream)
add_subdirectory(utility)

add_library(common INTERFACE)

target_link_libraries(
    common
    INTERFACE
        stream
        utility
)

# EOF
