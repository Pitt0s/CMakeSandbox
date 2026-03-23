#include <cassert>
#include <iostream>

#include <CMakeSandbox/math/vec2d.hpp>

int main() {
    using sandbox::math::Vec2d;

    // Construction and accessors
    const Vec2d v{3.0, 4.0};
    assert(v.x() == 3.0);
    assert(v.y() == 4.0);

    // Addition
    const Vec2d a{1.0, 2.0};
    const Vec2d b{3.0, 4.0};
    const Vec2d sum = a + b;
    assert(sum.x() == 4.0);
    assert(sum.y() == 6.0);

    // Subtraction
    const Vec2d diff = b - a;
    assert(diff.x() == 2.0);
    assert(diff.y() == 2.0);

    // Scalar multiplication
    const Vec2d scaled = a * 2.0;
    assert(scaled.x() == 2.0);
    assert(scaled.y() == 4.0);

    // Equality
    const Vec2d expected{1.0, 2.0};
    assert(a == expected);

    std::cout << "test_math PASSED\n";
    return 0;
}
