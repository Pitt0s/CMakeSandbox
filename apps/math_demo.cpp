// apps/math_demo.cpp
//
// Demonstrates the header-only math library:
//   - Vec2D<T> with Numeric concept
//   - Compile-time arithmetic and cross/dot products

#include "CMakeSandbox/math/vec2d.hpp"
#include "CMakeSandbox/version.hpp"

#include <iostream>

// A generic function constrained to Vec2D<T> for any Numeric T
template <CMakeSandbox::math::Numeric T>
void print_vec_info(std::string_view label, const CMakeSandbox::math::Vec2D<T>& v) {
    std::cout << "  " << label << " = " << v
              << " | length = " << v.length() << '\n';
}

int main() {
    using namespace CMakeSandbox::math;

    std::cout << "=== " << CMakeSandbox::version_string
              << " – Math Demo ===\n\n";

    // Integer vectors
    Vec2Di a{3, 4};
    Vec2Di b{1, 2};

    print_vec_info("a      ", a);
    print_vec_info("b      ", b);
    print_vec_info("a + b  ", a + b);
    print_vec_info("a - b  ", a - b);
    print_vec_info("a * 2  ", a * 2);
    print_vec_info("3 * b  ", 3 * b);

    std::cout << "\n  dot(a, b)   = " << a.dot(b) << '\n';
    std::cout << "  cross(a, b) = " << a.cross(b) << '\n';

    // Double vectors
    std::cout << '\n';
    Vec2Dd u{1.0, 0.0};
    Vec2Dd v{0.0, 1.0};

    print_vec_info("u      ", u);
    print_vec_info("v      ", v);
    std::cout << "  dot(u, v)   = " << u.dot(v) << "  (orthogonal vectors)\n";
    std::cout << "  cross(u, v) = " << u.cross(v) << '\n';

    std::cout << "\nDone.\n";
    return 0;
}
