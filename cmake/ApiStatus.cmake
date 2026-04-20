# cmake/ApiStatus.cmake
#
# CMake-level API-status tagging for CMakeSandbox targets.
#
# This module provides a single function, cmsb_set_target_status(), that
# records an API-support classification on a CMake target and emits
# appropriate diagnostics at configure time and at install time.
#
# Usage (in a library's CMakeLists.txt, after the target is defined):
#
#   cmsb_set_target_status(sandbox_bio_animals EXPERIMENTAL)
#   cmsb_set_target_status(sandbox_geo_shapes  SUPPORTED)
#
# Status values
# ─────────────
#   SUPPORTED   – stable, fully supported.  A STATUS message is emitted.
#   EXPERIMENTAL – API or behaviour may change between releases without notice.
#                  Emits a WARNING at configure time and at install time.
#   DEPRECATED  – scheduled for removal in a future release.
#                  Emits a WARNING at configure time and at install time.

# ─── Custom target property ───────────────────────────────────────────────────
# Registering the property makes it visible in cmake --build --target help,
# IDE property inspectors, and cmake_print_properties() output.
define_property(TARGET PROPERTY CMSB_API_STATUS
    BRIEF_DOCS "API support status: SUPPORTED, EXPERIMENTAL, or DEPRECATED"
    FULL_DOCS
        "Set by cmsb_set_target_status(). "
        "SUPPORTED:    stable and fully supported. "
        "EXPERIMENTAL: API or behaviour may change without notice; "
                      "avoid in production builds. "
        "DEPRECATED:   will be removed in a future release."
)

# ─── cmsb_set_target_status(<target> <STATUS>) ────────────────────────────────
#
# Assigns an API-status tag to a CMake target.
#   <target>  – any CMake target created with add_library() or add_executable()
#   <STATUS>  – SUPPORTED | EXPERIMENTAL | DEPRECATED
#
# Effects:
#   • Sets the CMSB_API_STATUS property on <target>.
#   • SUPPORTED:    emits message(STATUS ...) at configure time.
#   • EXPERIMENTAL: emits message(WARNING ...) at configure time and
#                   install(CODE ...) warning at cmake --install time.
#   • DEPRECATED:   same as EXPERIMENTAL but with a "will be removed" message.
function(cmsb_set_target_status target status)
    if(NOT status MATCHES "^(SUPPORTED|EXPERIMENTAL|DEPRECATED)$")
        message(FATAL_ERROR
            "cmsb_set_target_status(): STATUS must be one of "
            "SUPPORTED, EXPERIMENTAL, or DEPRECATED (got '${status}')"
        )
    endif()

    set_target_properties(${target} PROPERTIES CMSB_API_STATUS "${status}")

    if(status STREQUAL "SUPPORTED")
        message(STATUS
            "[CMakeSandbox] Target '${target}': SUPPORTED"
        )
    elseif(status STREQUAL "EXPERIMENTAL")
        message(WARNING
            "[CMakeSandbox] Target '${target}' is EXPERIMENTAL – "
            "its API and behaviour may change between releases without notice. "
            "Do not rely on it in production builds."
        )
        install(CODE
            "message(WARNING \"[CMakeSandbox] Installing EXPERIMENTAL target "
            "'${target}'. Its API may change without notice.\")"
        )
    elseif(status STREQUAL "DEPRECATED")
        message(WARNING
            "[CMakeSandbox] Target '${target}' is DEPRECATED and will be "
            "removed in a future release."
        )
        install(CODE
            "message(WARNING \"[CMakeSandbox] Installing DEPRECATED target "
            "'${target}'. It will be removed in a future release.\")"
        )
    endif()
endfunction()
