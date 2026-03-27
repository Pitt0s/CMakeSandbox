# cmake/ApiStatus.cmake
#
# API-status infrastructure for CMakeSandbox.
#
# Provides:
#   sandbox_api_status  (alias CMakeSandbox::api_status) – an INTERFACE library
#     that installs include/CMakeSandbox/api_status.hpp and, when
#     CMSB_ENABLE_EXPERIMENTAL is ON, propagates the CMSB_ENABLE_EXPERIMENTAL
#     preprocessor macro to all consumers of this target.
#
# CMake option:
#   CMSB_ENABLE_EXPERIMENTAL  (default: OFF)
#     When ON, every target that links CMakeSandbox::api_status receives the
#     CMSB_ENABLE_EXPERIMENTAL compile definition, suppressing the
#     [[deprecated]]-style diagnostic emitted by the CMSB_EXPERIMENTAL macro.
#
#     Downstream consumers that intentionally use experimental APIs can opt in
#     via FetchContent:
#
#       set(CMSB_ENABLE_EXPERIMENTAL ON CACHE BOOL "" FORCE)
#       FetchContent_MakeAvailable(CMakeSandbox)
#       target_link_libraries(my_app PRIVATE CMakeSandbox::api_status
#                                            CMakeSandbox::bio::animals)
#
#     Or by passing -DCMSB_ENABLE_EXPERIMENTAL directly to the compiler.

# ─── Option ──────────────────────────────────────────────────────────────────
option(CMSB_ENABLE_EXPERIMENTAL
    "Suppress deprecation warnings for experimental CMakeSandbox APIs"
    OFF
)

# ─── INTERFACE target ─────────────────────────────────────────────────────────
add_library(sandbox_api_status INTERFACE)
add_library(CMakeSandbox::api_status ALIAS sandbox_api_status)

target_sources(sandbox_api_status
    INTERFACE
        FILE_SET sandbox_api_status_headers
        TYPE HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/CMakeSandbox/api_status.hpp"
)

if(CMSB_ENABLE_EXPERIMENTAL)
    target_compile_definitions(sandbox_api_status INTERFACE
        CMSB_ENABLE_EXPERIMENTAL
    )
endif()

# ─── Install ─────────────────────────────────────────────────────────────────
include(GNUInstallDirs)

install(
    TARGETS sandbox_api_status
    EXPORT  CMakeSandboxTargets
    FILE_SET sandbox_api_status_headers
             DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
