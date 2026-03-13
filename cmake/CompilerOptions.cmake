# cmake/CompilerOptions.cmake
#
# Provides the helper function `cmsb_set_compiler_options(<target>)` which
# attaches PRIVATE compile options appropriate for the active compiler and
# build type.  Use PRIVATE so these flags never leak into consumer targets.

function(cmsb_set_compiler_options target)
    target_compile_options(${target} PRIVATE
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
endfunction()
