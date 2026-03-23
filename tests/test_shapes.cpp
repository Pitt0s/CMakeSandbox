// tests/test_shapes.cpp
//
// Tests for the geo::shapes library.
// Uses standard assert() – no external test framework required.
// Returns 0 on success, non-zero on failure (CTest compatible).

#include "CMakeSandbox/geo/shapes/circle.hpp"
#include "CMakeSandbox/geo/shapes/concepts.hpp"
#include "CMakeSandbox/geo/shapes/rectangle.hpp"
#include "CMakeSandbox/geo/shapes/triangle.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <numbers>

namespace shapes = CMakeSandbox::geo::shapes;

static constexpr double eps = 1e-9;

// ---------------------------------------------------------------------------
// Helper
// ---------------------------------------------------------------------------
static bool near(double a, double b) {
    return std::abs(a - b) < eps;
}

// ---------------------------------------------------------------------------
// Concept satisfaction checks (compile-time)
// ---------------------------------------------------------------------------
static_assert(shapes::Shape2D<shapes::Circle>);
static_assert(shapes::Shape2D<shapes::Rectangle>);
static_assert(shapes::Shape2D<shapes::Triangle>);

// ---------------------------------------------------------------------------
// Runtime tests
// ---------------------------------------------------------------------------
static void test_circle() {
    const shapes::Circle c{5.0};
    assert(c.name() == "Circle");
    assert(near(c.radius(), 5.0));
    assert(near(c.area(),      std::numbers::pi * 25.0));
    assert(near(c.perimeter(), 2.0 * std::numbers::pi * 5.0));
    std::cout << "  [PASS] Circle\n";
}

static void test_rectangle() {
    const shapes::Rectangle r{4.0, 3.0};
    assert(r.name() == "Rectangle");
    assert(near(r.width(),  4.0));
    assert(near(r.height(), 3.0));
    assert(near(r.area(),       12.0));
    assert(near(r.perimeter(),  14.0));
    std::cout << "  [PASS] Rectangle\n";
}

static void test_triangle() {
    // 3-4-5 right triangle
    const shapes::Triangle t{3.0, 4.0, 5.0};
    assert(t.name() == "Triangle");
    assert(near(t.side_a(), 3.0));
    assert(near(t.side_b(), 4.0));
    assert(near(t.side_c(), 5.0));
    assert(near(t.area(),       6.0));   // base*height/2 = 3*4/2
    assert(near(t.perimeter(), 12.0));
    std::cout << "  [PASS] Triangle\n";
}

static void test_virtual_dispatch() {
    // Polymorphic pointer to base
    const std::unique_ptr<shapes::Shape> shape =
        std::make_unique<shapes::Circle>(1.0);
    assert(shape->name() == "Circle");
    assert(near(shape->area(), std::numbers::pi));
    std::cout << "  [PASS] Virtual dispatch\n";
}

int main() {
    std::cout << "=== test_shapes ===\n";
    test_circle();
    test_rectangle();
    test_triangle();
    test_virtual_dispatch();
    std::cout << "All shape tests passed.\n";
    return 0;
}
