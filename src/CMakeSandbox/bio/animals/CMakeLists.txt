# src/CMakeSandbox/bio/animals/CMakeLists.txt
#
# Defines the sandbox_bio_animals library target.
# ALIAS: CMakeSandbox::bio::animals
#
# The library type (SHARED or STATIC) is controlled by the standard CMake
# variable BUILD_SHARED_LIBS (default: ON → shared).  Callers using
# FetchContent or the install can override it before including this project:
#   set(BUILD_SHARED_LIBS OFF)   # → static
#   FetchContent_MakeAvailable(CMakeSandbox)

# ============================================================================
# Target definition
# ============================================================================
add_library(sandbox_bio_animals)
add_library(CMakeSandbox::bio::animals ALIAS sandbox_bio_animals)

target_sources(sandbox_bio_animals
    PRIVATE
        animal.cpp
        dog.cpp
        cat.cpp
        bird.cpp
    PUBLIC
        FILE_SET sandbox_bio_animals_headers
        TYPE HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/bio/animals/animal.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/bio/animals/dog.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/bio/animals/cat.hpp"
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/bio/animals/bird.hpp"
)

target_link_libraries(sandbox_bio_animals PRIVATE CMakeSandbox::compiler_flags)

# The bio::animals classes are themselves marked CMSB_EXPERIMENTAL.
# Add CMSB_ENABLE_EXPERIMENTAL privately so the library's own translation
# units compile without spurious deprecated warnings when implementing the
# experimental API (the warning is intended for downstream consumers only).
target_compile_definitions(sandbox_bio_animals PRIVATE CMSB_ENABLE_EXPERIMENTAL)

# ============================================================================
# Install
# ============================================================================
include(GNUInstallDirs)

install(
    TARGETS sandbox_bio_animals
    EXPORT  CMakeSandboxTargets
    LIBRARY   DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE   DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME   DESTINATION "${CMAKE_INSTALL_BINDIR}"
    FILE_SET  sandbox_bio_animals_headers
              DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
