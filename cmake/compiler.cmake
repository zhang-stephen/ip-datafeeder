# Common Configurations for compilers

add_library(compiler_conf INTERFACE)

target_compile_features(
    compiler_conf
    INTERFACE
        cxx_std_20
)

target_compile_options(
    compiler_conf
    INTERFACE
        -Wall
        -Werror
        $<IF:$<BOOL:$<CONFIG:DEBUG>>,-g -O2,-O3>
)

target_include_directories(
    compiler_conf
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src/common
        ${PROJECT_BINARY_DIR}/include
)

# EOF