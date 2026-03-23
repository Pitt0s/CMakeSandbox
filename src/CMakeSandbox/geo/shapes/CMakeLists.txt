# src/CMakeSandbox/geo/shapes/CMakeLists.txt
#
# Defines the sandbox_geo_shapes library target and installs it.
# The ALIAS target CMakeSandbox::geo::shapes is used by consumers.
#
# The library type (SHARED or STATIC) is controlled by the standard CMake
# variable BUILD_SHARED_LIBS (default: ON → shared).  Callers using
# FetchContent or the install can override it before including this project:
#   set(BUILD_SHARED_LIBS OFF)   # → static
#   FetchContent_MakeAvailable(CMakeSandbox)

# ============================================================================
# Target definition
# ============================================================================
add_library(sandbox_geo_shapes)
add_library(CMakeSandbox::geo::shapes ALIAS sandbox_geo_shapes)

# Sources + public headers declared together via FILE_SET (CMake >= 3.23).
# BASE_DIRS controls the include root exposed to consumers.
# Note: FILE_SET BASE_DIRS automatically sets INTERFACE_INCLUDE_DIRECTORIES —
# target_include_directories() is not needed.
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

# Apply private compiler warnings / optimisation flags.
target_link_libraries(sandbox_geo_shapes PRIVATE CMakeSandbox::compiler_flags)

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
