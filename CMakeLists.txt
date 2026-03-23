cmake_minimum_required(VERSION 3.25)

# On macOS, Homebrew LLVM does not automatically include the macOS SDK sysroot,
# causing angle-bracket includes of system headers (pthread.h, sched.h, time.h,
# etc.) to fail. Detect and set the sysroot before project() so CMake passes it
# to every compiler and linker invocation via -isysroot.
if(APPLE AND NOT DEFINED CMAKE_OSX_SYSROOT)
    execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE _macos_sdk_path
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    if(_macos_sdk_path)
        set(CMAKE_OSX_SYSROOT "${_macos_sdk_path}" CACHE PATH "macOS SDK sysroot")
    endif()
    unset(_macos_sdk_path)
endif()

project(
    CMakeSandbox
    VERSION 0.1.0
    DESCRIPTION "C++20 project structure sandbox using the Pitchfork Layout"
    LANGUAGES CXX
)

# ── C++ standard ─────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Global warning flags ──────────────────────────────────────────────────────
add_compile_options(
    -Wall -Wextra -Wpedantic
    -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
    -Woverloaded-virtual -Wsign-conversion
)

# ── Build-type defaults ───────────────────────────────────────────────────────
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG)
endif()

# ── Generated headers ─────────────────────────────────────────────────────────
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/CMakeSandbox/version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/CMakeSandbox/version.hpp"
    @ONLY
)

# ── Testing ───────────────────────────────────────────────────────────────────
enable_testing()

# ── Subdirectories ────────────────────────────────────────────────────────────
add_subdirectory(src/CMakeSandbox/geo/shapes)
add_subdirectory(src/CMakeSandbox/bio/animals)
add_subdirectory(src/CMakeSandbox/math)

add_subdirectory(apps)
add_subdirectory(tests)
