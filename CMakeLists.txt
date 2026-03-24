cmake_minimum_required(VERSION 3.26)

project(CMakeSandbox
    VERSION 0.1.0
    DESCRIPTION "CMake Sandbox for PFL with Separate Header Placement (C++20)"
    HOMEPAGE_URL "https://github.com/Pitt0s/CMakeSandbox"
    LANGUAGES CXX C
)

# ============================================================================
# Options
# ============================================================================
option(CMSB_BUILD_APPS   "Build example applications" ON)
option(CMSB_BUILD_TESTS  "Build tests"                 ON)
option(CMSB_ENABLE_CLANG_TIDY "Enable clang-tidy analysis" OFF)

# BUILD_SHARED_LIBS is a standard CMake variable that controls whether
# add_library() without an explicit STATIC/SHARED keyword produces a shared
# or a static library.  Exposing it here lets callers (FetchContent, CLI,
# presets) choose the linkage type they need:
#   -DBUILD_SHARED_LIBS=ON  → shared (.so/.dylib/.dll)  [default]
#   -DBUILD_SHARED_LIBS=OFF → static (.a/.lib)
option(BUILD_SHARED_LIBS "Build shared libraries (OFF = static)" ON)
mark_as_advanced(BUILD_SHARD_LIBS)

# ============================================================================
# Global C++ standard settings  (no per-target duplication needed)
# ============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# This project uses only traditional #include-based headers; no C++20 named
# modules (import/export module) are present.  On CMake 3.28+ we can explicitly
# disable module scanning, which avoids invoking clang-scan-deps on toolchains
# where it is not fully configured (e.g., Homebrew LLVM on macOS).
# On CMake 3.26/3.27 this variable does not exist; module scanning is simply
# not performed because those versions do not enable it by default.
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.28")
    set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
endif()

# Export compile commands for IDEs / clang-based tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Additional CMake modules
# ============================================================================
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(CompilerOptions)

# ============================================================================
# Optional: clang-tidy (enable via -DCMSB_ENABLE_CLANG_TIDY=ON or preset)
# ============================================================================
if(CMSB_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
    set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        "--config-file=${PROJECT_SOURCE_DIR}/.clang-tidy"
    )
    message(STATUS "clang-tidy enabled: ${CLANG_TIDY_EXE}")
endif()

# ============================================================================
# Generated headers (Version.hpp)
# ============================================================================
configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/Version.hpp.in"
    "${PROJECT_BINARY_DIR}/include/CMakeSandbox/version.hpp"
    @ONLY
)

# INTERFACE target that propagates the generated include directory.
# All library targets that need version info link against this.
add_library(sandbox_version INTERFACE)
add_library(CMakeSandbox::version ALIAS sandbox_version)
target_include_directories(sandbox_version INTERFACE
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ============================================================================
# Libraries (defined hierarchically under src/)
# ============================================================================
add_subdirectory(src/CMakeSandbox)

# ============================================================================
# Applications
# ============================================================================
if(CMSB_BUILD_APPS)
    add_subdirectory(apps)
endif()

# ============================================================================
# Tests
# ============================================================================
if(CMSB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ============================================================================
# Install rules
# ============================================================================
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install the generated version header separately (it lives in the build tree)
install(
    FILES "${PROJECT_BINARY_DIR}/include/CMakeSandbox/version.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CMakeSandbox"
)

# Install the INTERFACE version target
install(
    TARGETS sandbox_version
    EXPORT  CMakeSandboxTargets
)

# Generate and install the package version file
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/cmake/CMakeSandboxConfigVersion.cmake"
    VERSION       ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Generate the package config file from the template
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/CMakeSandboxConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/cmake/CMakeSandboxConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CMakeSandbox"
)

# Install cmake config files
install(
    FILES
        "${PROJECT_BINARY_DIR}/cmake/CMakeSandboxConfig.cmake"
        "${PROJECT_BINARY_DIR}/cmake/CMakeSandboxConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CMakeSandbox"
)

# Install the targets export file (used by CMakeSandboxConfig.cmake)
install(
    EXPORT CMakeSandboxTargets
    FILE       CMakeSandboxTargets.cmake
    NAMESPACE  CMakeSandbox::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CMakeSandbox"
)
