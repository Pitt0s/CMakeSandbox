// tests/test_math.cpp
//
// Tests for the math header-only library.

#include "CMakeSandbox/math/vec2d.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

using namespace CMakeSandbox::math;

static constexpr double eps = 1e-9;

static bool near(double a, double b) {
    return std::abs(a - b) < eps;
}

// compile-time concept checks
static_assert(Numeric<int>);
static_assert(Numeric<float>);
static_assert(Numeric<double>);
// std::string is not arithmetic
static_assert(!Numeric<std::string>);

// compile-time arithmetic (use explicit types to avoid deduction issues)
static_assert(Vec2Di{3, 4} + Vec2Di{1, 2} == Vec2Di{4, 6});
static_assert(Vec2Di{3, 4} - Vec2Di{1, 2} == Vec2Di{2, 2});
static_assert((Vec2Di{3, 4} * 2)           == Vec2Di{6, 8});
static_assert(Vec2Di{3, 4}.dot(Vec2Di{1, 2}) == 11);
static_assert(Vec2Di{3, 4}.cross(Vec2Di{1, 2}) == 2);

static void test_arithmetic() {
    const Vec2Dd a{3.0, 4.0};
    const Vec2Dd b{1.0, 2.0};

    // Store results in variables to avoid the assert-macro / comma-in-braces issue
    const Vec2Dd sum  = a + b;  assert(sum  == (Vec2Dd{4.0, 6.0}));
    const Vec2Dd diff = a - b;  assert(diff == (Vec2Dd{2.0, 2.0}));
    const Vec2Dd sa   = a * 2.0; assert(sa  == (Vec2Dd{6.0, 8.0}));
    const Vec2Dd sb   = 2.0 * a; assert(sb  == (Vec2Dd{6.0, 8.0}));
    std::cout << "  [PASS] Vec2D arithmetic\n";
}

static void test_dot_cross() {
    const Vec2Dd a{3.0, 0.0};
    const Vec2Dd b{0.0, 4.0};

    assert(near(a.dot(b),   0.0));
    assert(near(a.cross(b), 12.0));
    std::cout << "  [PASS] dot / cross\n";
}

static void test_length() {
    const Vec2Di a{3, 4};
    assert(near(a.length(), 5.0));

    const Vec2Dd u{1.0, 0.0};
    assert(near(u.length(), 1.0));
    std::cout << "  [PASS] length\n";
}

int main() {
    std::cout << "=== test_math ===\n";
    test_arithmetic();
    test_dot_cross();
    test_length();
    std::cout << "All math tests passed.\n";
    return 0;
}
