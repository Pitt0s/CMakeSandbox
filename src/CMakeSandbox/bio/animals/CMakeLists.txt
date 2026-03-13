# src/CMakeSandbox/bio/animals/CMakeLists.txt
#
# Defines the sandbox_bio_animals SHARED library target.
# ALIAS: CMakeSandbox::bio::animals

# ============================================================================
# Target definition
# ============================================================================
add_library(sandbox_bio_animals SHARED)
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

target_include_directories(sandbox_bio_animals
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

cmsb_set_compiler_options(sandbox_bio_animals)

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
