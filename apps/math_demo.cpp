#include <iostream>

#include <CMakeSandbox/math/vec2d.hpp>

int main() {
    using sandbox::math::Vec2d;

    const Vec2d a{1.0, 2.0};
    const Vec2d b{3.0, 4.0};
    const Vec2d c = a + b;

    std::cout << a << " + " << b << " = " << c << '\n';
    std::cout << a << " - " << b << " = " << (a - b) << '\n';
    std::cout << a << " * 3 = " << (a * 3.0) << '\n';

    return 0;
}
