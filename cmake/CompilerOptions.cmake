# cmake/CompilerOptions.cmake
#
# Defines the INTERFACE library `sandbox_compiler_flags` (aliased as
# `CMakeSandbox::compiler_flags`) that carries all project-internal warning
# and optimisation flags.
#
# Usage in library / executable CMakeLists:
#   target_link_libraries(<target> PRIVATE CMakeSandbox::compiler_flags)
#
# Because the linkage is PRIVATE, the INTERFACE_COMPILE_OPTIONS of
# sandbox_compiler_flags become *private* to <target> – they are applied to
# <target>'s own compilation but never propagate to consumers.  This is how
# we enforce "no -Wall leak into downstream projects" with a single, reusable
# target instead of a function call on every target.

add_library(sandbox_compiler_flags INTERFACE)
add_library(CMakeSandbox::compiler_flags ALIAS sandbox_compiler_flags)

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
