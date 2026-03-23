# ── Helper macro ──────────────────────────────────────────────────────────────
macro(add_sandbox_test NAME)
    add_executable(${NAME} ${NAME}.cpp)
    target_include_directories(${NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
    target_include_directories(${NAME} PRIVATE "${CMAKE_BINARY_DIR}/include")
    target_link_libraries(${NAME} PRIVATE ${ARGN})
    add_test(NAME ${NAME} COMMAND ${NAME})
endmacro()

# ── Tests ─────────────────────────────────────────────────────────────────────
add_sandbox_test(test_math    CMakeSandbox::math)
add_sandbox_test(test_shapes  CMakeSandbox::geo::shapes)
add_sandbox_test(test_animals CMakeSandbox::bio::animals)
add_sandbox_test(test_version)
