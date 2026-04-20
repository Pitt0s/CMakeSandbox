# apps/CMakeLists.txt
#
# Each application is a standalone executable that links one or more
# CMakeSandbox libraries.  All targets use PRIVATE linkage – app-level
# dependencies do not propagate further.

include(GNUInstallDirs)

# ============================================================================
# shapes_demo – geometry + math utilities
# ============================================================================
add_executable(shapes_demo shapes_demo.cpp)
target_link_libraries(shapes_demo PRIVATE
    CMakeSandbox::geo::shapes
    CMakeSandbox::math
    CMakeSandbox::version
    CMakeSandbox::compiler_flags
)

install(TARGETS shapes_demo RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# ============================================================================
# animals_demo – biology
# ============================================================================
add_executable(animals_demo animals_demo.cpp)
target_link_libraries(animals_demo PRIVATE
    CMakeSandbox::bio::animals
    CMakeSandbox::version
    CMakeSandbox::compiler_flags
)

install(TARGETS animals_demo RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# ============================================================================
# math_demo – header-only math library
# ============================================================================
add_executable(math_demo math_demo.cpp)
target_link_libraries(math_demo PRIVATE
    CMakeSandbox::math
    CMakeSandbox::version
    CMakeSandbox::compiler_flags
)

install(TARGETS math_demo RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
