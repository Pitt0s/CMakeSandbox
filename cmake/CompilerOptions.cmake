# cmake/CompilerOptions.cmake
#
# Defines the INTERFACE library `sandbox_compiler_flags` (aliased as
# `CMakeSandbox::compiler_flags`) that carries all project-internal warning,
# optimisation, and platform-portability flags.
#
# Usage in library / executable CMakeLists:
#   target_link_libraries(<target> PRIVATE CMakeSandbox::compiler_flags)
#
# Because the linkage is PRIVATE, the INTERFACE_COMPILE_OPTIONS of
# sandbox_compiler_flags become *private* to <target> – they are applied to
# <target>'s own compilation but never propagate to consumers.  This is how
# we enforce "no -Wall leak into downstream projects" with a single, reusable
# target instead of a function call on every target.
#
# Threads::Threads is included here so that every target gets correct pthread
# linkage on all platforms.  Clang (especially with lld or on systems where
# libpthread is not auto-linked) requires the flag to be stated explicitly;
# GCC and MSVC accept it silently.  find_package(Threads) is the canonical
# CMake abstraction: it expands to -pthread on POSIX, nothing extra on MSVC,
# and handles macOS / Windows transparently.

find_package(Threads REQUIRED)

add_library(sandbox_compiler_flags INTERFACE)
add_library(CMakeSandbox::compiler_flags ALIAS sandbox_compiler_flags)

# Propagate pthread / threading support to every target that links this library.
target_link_libraries(sandbox_compiler_flags INTERFACE Threads::Threads)

target_compile_options(sandbox_compiler_flags INTERFACE
    # ---- GCC -------------------------------------------------------
    $<$<CXX_COMPILER_ID:GNU>:
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Woverloaded-virtual
        -Wsign-conversion
    >
    # ---- Clang / Apple Clang ---------------------------------------
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Woverloaded-virtual
        -Wsign-conversion
    >
    # ---- MSVC ------------------------------------------------------
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4
        /permissive-
    >

    # ---- Per build-type optimisations ------------------------------
    $<$<CONFIG:Debug>:
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
            -g
            -O0
        >
        $<$<CXX_COMPILER_ID:MSVC>:/Od /Zi>
    >
    $<$<CONFIG:Release>:
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
            -O3
        >
        $<$<CXX_COMPILER_ID:MSVC>:/O2>
    >
    $<$<CONFIG:RelWithDebInfo>:
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
            -O2
            -g
        >
    >
)
