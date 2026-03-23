#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>

#include <CMakeSandbox/geo/shapes/circle.hpp>
#include <CMakeSandbox/geo/shapes/rectangle.hpp>
#include <CMakeSandbox/geo/shapes/triangle.hpp>

static bool approx(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) < eps;
}

int main() {
    using namespace sandbox::geo;

    // Circle
    {
        Circle c{5.0};
        assert(c.name() == "Circle");
        assert(c.radius() == 5.0);
        assert(approx(c.area(),      std::numbers::pi * 25.0));
        assert(approx(c.perimeter(), 2.0 * std::numbers::pi * 5.0));
    }

    // Rectangle
    {
        Rectangle r{4.0, 6.0};
        assert(r.name() == "Rectangle");
        assert(r.width()  == 4.0);
        assert(r.height() == 6.0);
        assert(approx(r.area(),      24.0));
        assert(approx(r.perimeter(), 20.0));
    }

    // Triangle (3-4-5 right triangle)
    {
        Triangle t{3.0, 4.0, 5.0};
        assert(t.name() == "Triangle");
        assert(approx(t.area(),       6.0));
        assert(approx(t.perimeter(), 12.0));
    }

    std::cout << "test_shapes PASSED\n";
    return 0;
}
