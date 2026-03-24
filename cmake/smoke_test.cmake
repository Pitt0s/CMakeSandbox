# cmake/smoke_test.cmake
#
# Generic driver for the standalone smoke test project (tests/smoke/).
# Invoked from CTest via add_test(... COMMAND cmake ... -P cmake/smoke_test.cmake).
#
# Required variables (pass via -D on the command line):
#   SMOKE_SOURCE_DIR  – absolute path to tests/smoke/
#   SMOKE_BUILD_DIR   – absolute path where the smoke project should be built
#
# Optional variables:
#   CMAKE_PREFIX_PATH     – install prefix to search; used for the find_package mode
#   SMOKE_USE_FETCHCONTENT – when ON, uses FetchContent SOURCE_DIR instead of find_package
#   CMSB_SOURCE_DIR       – path to the CMakeSandbox source root; required when
#                            SMOKE_USE_FETCHCONTENT=ON

foreach(var SMOKE_SOURCE_DIR SMOKE_BUILD_DIR)
    if(NOT DEFINED "${var}")
        message(FATAL_ERROR "[smoke] ${var} must be defined (pass -D${var}=...)")
    endif()
endforeach()

# ── Build the configure argument list ─────────────────────────────────────────
set(_cmake_args
    -S "${SMOKE_SOURCE_DIR}"
    -B "${SMOKE_BUILD_DIR}"
    -DCMAKE_CXX_STANDARD=20
)

if(DEFINED CMAKE_PREFIX_PATH AND NOT CMAKE_PREFIX_PATH STREQUAL "")
    list(APPEND _cmake_args "-DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
endif()

if(SMOKE_USE_FETCHCONTENT)
    list(APPEND _cmake_args -DSMOKE_USE_FETCHCONTENT=ON)
    if(NOT DEFINED CMSB_SOURCE_DIR OR CMSB_SOURCE_DIR STREQUAL "")
        message(FATAL_ERROR
            "[smoke] CMSB_SOURCE_DIR must be defined when SMOKE_USE_FETCHCONTENT=ON")
    endif()
    list(APPEND _cmake_args "-DCMSB_SOURCE_DIR=${CMSB_SOURCE_DIR}")
endif()

# ── Configure ─────────────────────────────────────────────────────────────────
message(STATUS "[smoke] configuring ${SMOKE_SOURCE_DIR}")
execute_process(
    COMMAND "${CMAKE_COMMAND}" ${_cmake_args}
    RESULT_VARIABLE _rc
    COMMAND_ECHO STDOUT
)
if(NOT _rc EQUAL 0)
    message(FATAL_ERROR "[smoke] configure step failed (rc=${_rc})")
endif()

# ── Build ─────────────────────────────────────────────────────────────────────
message(STATUS "[smoke] building")
execute_process(
    COMMAND "${CMAKE_COMMAND}" --build "${SMOKE_BUILD_DIR}"
    RESULT_VARIABLE _rc
    COMMAND_ECHO STDOUT
)
if(NOT _rc EQUAL 0)
    message(FATAL_ERROR "[smoke] build step failed (rc=${_rc})")
endif()

# ── Run tests ─────────────────────────────────────────────────────────────────
message(STATUS "[smoke] running tests")
execute_process(
    COMMAND "${CMAKE_CTEST_COMMAND}"
        --test-dir "${SMOKE_BUILD_DIR}"
        --output-on-failure
    RESULT_VARIABLE _rc
    COMMAND_ECHO STDOUT
)
if(NOT _rc EQUAL 0)
    message(FATAL_ERROR "[smoke] test step failed (rc=${_rc})")
endif()

message(STATUS "[smoke] all steps passed")
