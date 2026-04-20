# src/CMakeSandbox/math/CMakeLists.txt
#
# Defines the sandbox_math INTERFACE (header-only) library.
# ALIAS: CMakeSandbox::math
#
# Because math/ is header-only there are no compiled translation units here.
# We use an INTERFACE target and declare the headers via a FILE_SET so that
# cmake --install correctly copies them and they appear in the export set.
#
# Note: no target_include_directories() needed.  FILE_SET BASE_DIRS
# automatically populates INTERFACE_INCLUDE_DIRECTORIES for both the build
# interface (${PROJECT_SOURCE_DIR}/include) and the install interface
# (derived from the FILE_SET DESTINATION given in install(TARGETS ...)).
# Consumers therefore write: #include <CMakeSandbox/math/vec2d.hpp>

# ============================================================================
# Target definition
# ============================================================================
add_library(sandbox_math INTERFACE)
add_library(CMakeSandbox::math ALIAS sandbox_math)

target_sources(sandbox_math
    INTERFACE
        FILE_SET sandbox_math_headers
        TYPE HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/math/vec2d.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/math/algorithms.hpp"
)

# math::algorithms uses geo::shapes concepts
target_link_libraries(sandbox_math INTERFACE CMakeSandbox::geo::shapes)

# Tag this target's API-support status.
cmsb_set_target_status(sandbox_math SUPPORTED)

# ============================================================================
# Install
# ============================================================================
include(GNUInstallDirs)

install(
    TARGETS sandbox_math
    EXPORT  CMakeSandboxTargets
    FILE_SET sandbox_math_headers
             DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
