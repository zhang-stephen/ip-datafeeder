# commands definitions for ipdf building
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

include(CMakeParseArguments)

macro(increase_message_indent)
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
endmacro()

macro(decrease_message_indent)
    list(POP_BACK CMAKE_MESSAGE_INDENT)
endmacro()

function(ipdf_create_ut COMPONENT)
    set(options)
    set(oneValueArgs COMPONENT)
    set(multiValueArgs INCLUDES LIBRARIES SOURCES)
    set(UT_MODULE_NAME ${IPDF_UT_PREFIX}_${COMPONENT})
    cmake_parse_arguments(UT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message(STATUS "creating ut -> ${UT_MODULE_NAME}...")
    increase_message_indent()

    foreach(sub ${UT_INCLUDES})
        message(STATUS "adding include dir: ${sub}")
    endforeach()

    foreach(sub ${UT_LIBRARIES})
        message(STATUS "adding dependency: ${sub}")
    endforeach()

    foreach(sub ${UT_SOURCES})
        message(STATUS "adding soruce file: ${sub}")
    endforeach()

    decrease_message_indent()

    add_executable(${UT_MODULE_NAME})

    target_sources(
        ${UT_MODULE_NAME}
        PRIVATE
            ${UT_SOURCES}
    )

    target_include_directories(
        ${UT_MODULE_NAME}
        PRIVATE
            ${UT_INCLUDES}
    )

    target_link_libraries(
        ${UT_MODULE_NAME}
        PRIVATE
            ${UT_LIBRARIES}
    )

    add_test(
        NAME ${UT_MODULE_NAME}
        COMMAND $<TARGET_FILE:${UT_MODULE_NAME}>
    )
endfunction()

# EOF
