# subdirectory entrypoint
# try to pack modules as individual libraries, instead of packing the whole src/ as single library

configure_file(
    common/config.hh.in
    ${CMAKE_BINARY_DIR}/include/config.hh
    NEWLINE_STYLE LF
)

add_subdirectory(log)

# EOF