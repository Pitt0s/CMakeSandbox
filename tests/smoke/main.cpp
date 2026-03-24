// tests/smoke/main.cpp
//
// Minimal consumer of the installed (or FetchContent-fetched) CMakeSandbox library.
// Verifies that public headers are reachable, the library links correctly,
// and that the core functionality is operational.
//
// Returns 0 on success; a failed assert() causes a non-zero exit via abort().

#include <CMakeSandbox/geo/shapes/circle.hpp>
#include <CMakeSandbox/math/vec2d.hpp>
#include <CMakeSandbox/version.hpp>

#include <cassert>
#include <cmath>
#include <iostream>

int main()
{
    // ── geo::shapes ───────────────────────────────────────────────────────────
    CMakeSandbox::geo::shapes::Circle c{3.0};
    assert(c.area() > 0.0);
    assert(c.name() == "Circle");

    // ── math ──────────────────────────────────────────────────────────────────
    CMakeSandbox::math::Vec2Dd a{3.0, 4.0};
    assert(std::abs(a.length() - 5.0) < 1e-9);

    // ── version ───────────────────────────────────────────────────────────────
    static_assert(CMakeSandbox::version_major >= 0);
    assert(!CMakeSandbox::version_string.empty());

    std::cout << "smoke_test PASSED  (CMakeSandbox " << CMakeSandbox::version_string << ")\n";
    return 0;
}
