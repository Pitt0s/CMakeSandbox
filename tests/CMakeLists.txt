# tests/CMakeLists.txt
#
# Each test is a standalone executable (no external test framework required).
# Tests are registered with CTest so they run via `ctest` or `cmake --build . --target test`.

include(GNUInstallDirs)

# ============================================================================
# Helper macro – reduces boilerplate
# ============================================================================
macro(cmsb_add_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE ${ARGN} CMakeSandbox::compiler_flags)
    add_test(NAME ${name} COMMAND ${name})
endmacro()

# ============================================================================
# Tests
# ============================================================================
cmsb_add_test(test_shapes
    CMakeSandbox::geo::shapes
)

cmsb_add_test(test_animals
    CMakeSandbox::bio::animals
)

cmsb_add_test(test_math
    CMakeSandbox::math
)

cmsb_add_test(test_version
    CMakeSandbox::version
)

# ============================================================================
# Smoke tests (optional – enabled via -DCMSB_BUILD_SMOKE_TEST=ON)
# ============================================================================
# These tests build the standalone consumer project in tests/smoke/ in a
# separate cmake invocation, validating that:
#   smoke_find_package  – all install() rules are present and find_package works
#   smoke_fetchcontent  – FetchContent SOURCE_DIR integration works
# Note: smoke_find_package requires cmake --build --target install to have run
#       before ctest (handled automatically by the smoke-* workflow presets).
if(CMSB_BUILD_SMOKE_TEST)
    set(_smoke_src  "${PROJECT_SOURCE_DIR}/tests/smoke")
    set(_smoke_drv  "${PROJECT_SOURCE_DIR}/cmake/smoke_test.cmake")
    set(_smoke_bdir "${CMAKE_CURRENT_BINARY_DIR}/smoke")

    # find_package variant: validates installed package config and headers
    add_test(
        NAME smoke_find_package
        COMMAND "${CMAKE_COMMAND}"
            "-DSMOKE_SOURCE_DIR=${_smoke_src}"
            "-DSMOKE_BUILD_DIR=${_smoke_bdir}_install"
            "-DCMAKE_PREFIX_PATH=${CMAKE_INSTALL_PREFIX}"
            -P "${_smoke_drv}"
    )

    # FetchContent variant: validates in-source integration without install
    add_test(
        NAME smoke_fetchcontent
        COMMAND "${CMAKE_COMMAND}"
            "-DSMOKE_SOURCE_DIR=${_smoke_src}"
            "-DSMOKE_BUILD_DIR=${_smoke_bdir}_fetch"
            -DSMOKE_USE_FETCHCONTENT:BOOL=ON
            "-DCMSB_SOURCE_DIR=${PROJECT_SOURCE_DIR}"
            -P "${_smoke_drv}"
    )
endif()
