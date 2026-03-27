// include/CMakeSandbox/api_status.hpp
//
// Compile-time API-status annotations for CMakeSandbox.
//
// Three macros are provided for use on class, struct, function, and type
// declarations to communicate their support status to downstream consumers.
// Place each macro directly after the leading keyword (class/struct/void/…):
//
//   class CMSB_SUPPORTED   Circle { … };
//   class CMSB_EXPERIMENTAL Animal { … };
//   CMSB_DEPRECATED("Use bar() instead.") void foo();
//
// ─── CMSB_SUPPORTED ──────────────────────────────────────────────────────────
//   Marks an API as stable and fully supported.
//   Expands to nothing; serves as explicit documentation in the source.
//
// ─── CMSB_DEPRECATED("reason") ───────────────────────────────────────────────
//   Marks an API as deprecated.  Emits a compiler warning at every use site.
//   Define CMSB_NO_DEPRECATED_WARNINGS to silence all deprecated warnings.
//
// ─── CMSB_EXPERIMENTAL ───────────────────────────────────────────────────────
//   Marks an API as experimental: behaviour, signature, or existence may
//   change between minor releases without notice.  Emits a deprecation-style
//   compiler warning at every use site.
//   Define CMSB_ENABLE_EXPERIMENTAL (e.g. -DCMSB_ENABLE_EXPERIMENTAL) to
//   suppress the warning and signal an intentional opt-in to the unstable API.

#pragma once

// ─── SUPPORTED ───────────────────────────────────────────────────────────────
// Documentation-only annotation.  Expands to nothing.
#define CMSB_SUPPORTED

// ─── DEPRECATED ──────────────────────────────────────────────────────────────
// Emits a compiler deprecation warning at every use site.
// Define CMSB_NO_DEPRECATED_WARNINGS to silence all deprecated warnings.
#ifdef CMSB_NO_DEPRECATED_WARNINGS
#  define CMSB_DEPRECATED(msg)
#else
#  define CMSB_DEPRECATED(msg) [[deprecated(msg)]]
#endif

// ─── EXPERIMENTAL ────────────────────────────────────────────────────────────
// Emits a deprecation-style warning to alert consumers that the API is
// experimental.  Define CMSB_ENABLE_EXPERIMENTAL (e.g. pass
// -DCMSB_ENABLE_EXPERIMENTAL to the compiler) to suppress the warning and
// signal an intentional opt-in to the unstable API.
#ifdef CMSB_ENABLE_EXPERIMENTAL
#  define CMSB_EXPERIMENTAL
#else
#  define CMSB_EXPERIMENTAL                                                   \
     [[deprecated("Experimental API – may change without notice. "           \
                  "Define CMSB_ENABLE_EXPERIMENTAL to suppress this warning.")]]
#endif
