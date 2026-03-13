# src/CMakeSandbox/geo/shapes/CMakeLists.txt
#
# Defines the sandbox_geo_shapes SHARED library target and installs it.
# The ALIAS target CMakeSandbox::geo::shapes is used by consumers.

# ============================================================================
# Target definition
# ============================================================================
add_library(sandbox_geo_shapes SHARED)
add_library(CMakeSandbox::geo::shapes ALIAS sandbox_geo_shapes)

# Sources + public headers declared together via FILE_SET (CMake >= 3.23).
# BASE_DIRS controls the include root exposed to consumers.
target_sources(sandbox_geo_shapes
    PRIVATE
        circle.cpp
        rectangle.cpp
        triangle.cpp
    PUBLIC
        FILE_SET sandbox_geo_shapes_headers
        TYPE HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/geo/shapes/concepts.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/geo/shapes/shape.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/geo/shapes/circle.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/geo/shapes/rectangle.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/geo/shapes/triangle.hpp"
)

# Include directories: consumers get the installed path after install().
target_include_directories(sandbox_geo_shapes
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Apply private compiler warnings / optimisation flags.
cmsb_set_compiler_options(sandbox_geo_shapes)

# ============================================================================
# Install
# ============================================================================
include(GNUInstallDirs)

install(
    TARGETS sandbox_geo_shapes
    EXPORT  CMakeSandboxTargets
    LIBRARY   DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE   DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME   DESTINATION "${CMAKE_INSTALL_BINDIR}"
    FILE_SET  sandbox_geo_shapes_headers
              DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
