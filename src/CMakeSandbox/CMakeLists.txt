# src/CMakeSandbox/CMakeLists.txt
#
# Top-level source aggregation.
#
# Structural pattern from PFL:
#   - Each sub-domain defines its own fine-grained library targets.
#   - INTERFACE "umbrella" targets (e.g. sandbox_geo, sandbox_bio) aggregate
#     all sub-targets within a domain so consumers can link a single target.

# ============================================================================
# Leaf libraries
# ============================================================================
add_subdirectory(geo/shapes)
add_subdirectory(bio/animals)
add_subdirectory(math)

# ============================================================================
# Umbrella / grouping INTERFACE targets
# ============================================================================

# --- Geometry domain --------------------------------------------------------
add_library(sandbox_geo INTERFACE)
add_library(CMakeSandbox::geo ALIAS sandbox_geo)
target_link_libraries(sandbox_geo INTERFACE
    CMakeSandbox::geo::shapes
)

# --- Biology domain ---------------------------------------------------------
add_library(sandbox_bio INTERFACE)
add_library(CMakeSandbox::bio ALIAS sandbox_bio)
target_link_libraries(sandbox_bio INTERFACE
    CMakeSandbox::bio::animals
)

# ============================================================================
# Install umbrella targets (no headers – they are INTERFACE only)
# ============================================================================
include(GNUInstallDirs)

install(
    TARGETS sandbox_geo sandbox_bio
    EXPORT  CMakeSandboxTargets
)
