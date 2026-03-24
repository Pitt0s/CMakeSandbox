# tests/smoke/CMakeLists.txt
#
# Standalone consumer project used to validate the CMakeSandbox library.
# It can be driven in two ways:
#
#   1. find_package (default)  – tests install rules; requires a prior install:
#        cmake -S tests/smoke -B build/smoke \
#              -DCMAKE_PREFIX_PATH=<install-prefix>
#
#   2. FetchContent SOURCE_DIR – tests in-source integration without install:
#        cmake -S tests/smoke -B build/smoke \
#              -DSMOKE_USE_FETCHCONTENT=ON \
#              -DCMSB_SOURCE_DIR=<path-to-CMakeSandbox-root>
#
# Both modes compile the same main.cpp and register a CTest test.
# The cmake/smoke_test.cmake driver script runs this project end-to-end.

cmake_minimum_required(VERSION 3.26)
project(CMakeSandboxSmokeTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Acquire CMakeSandbox ───────────────────────────────────────────────────────
option(SMOKE_USE_FETCHCONTENT
    "Acquire CMakeSandbox via FetchContent SOURCE_DIR instead of find_package"
    OFF)

if(SMOKE_USE_FETCHCONTENT)
    if(NOT DEFINED CMSB_SOURCE_DIR)
        message(FATAL_ERROR
            "CMSB_SOURCE_DIR must be set when SMOKE_USE_FETCHCONTENT=ON\n"
            "Pass -DCMSB_SOURCE_DIR=<path-to-CMakeSandbox-root>")
    endif()

    include(FetchContent)

    # Disable apps and tests so only the library targets are built.
    set(CMSB_BUILD_APPS  OFF CACHE BOOL "" FORCE)
    set(CMSB_BUILD_TESTS OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(CMakeSandbox
        SOURCE_DIR "${CMSB_SOURCE_DIR}"
    )
    FetchContent_MakeAvailable(CMakeSandbox)
else()
    find_package(CMakeSandbox REQUIRED)
endif()

# ── Smoke test executable ──────────────────────────────────────────────────────
add_executable(smoke_test main.cpp)
target_link_libraries(smoke_test PRIVATE
    CMakeSandbox::geo::shapes
    CMakeSandbox::math
    CMakeSandbox::version
)

# ── Register with CTest ────────────────────────────────────────────────────────
enable_testing()
add_test(NAME smoke_test COMMAND smoke_test)
