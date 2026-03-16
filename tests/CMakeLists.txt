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
