// apps/shapes_demo.cpp
//
// Demonstrates both runtime polymorphism (Shape base class / virtual dispatch)
// and compile-time polymorphism (Shape2D concept + generic algorithms).

#include "CMakeSandbox/geo/shapes/circle.hpp"
#include "CMakeSandbox/geo/shapes/concepts.hpp"
#include "CMakeSandbox/geo/shapes/rectangle.hpp"
#include "CMakeSandbox/geo/shapes/triangle.hpp"
#include "CMakeSandbox/math/algorithms.hpp"
#include "CMakeSandbox/version.hpp"

#include <array>
#include <iostream>
#include <memory>
#include <vector>

// ---------------------------------------------------------------------------
// Compile-time polymorphism: generic function constrained by a concept
// ---------------------------------------------------------------------------

template <CMakeSandbox::geo::shapes::Shape2D S>
void describe(const S& shape) {
    std::cout << "  [compile-time dispatch] ";
    CMakeSandbox::math::print_shape_info(shape);
}

// ---------------------------------------------------------------------------
// Runtime polymorphism: through the abstract Shape base class
// ---------------------------------------------------------------------------

void describe_runtime(const CMakeSandbox::geo::shapes::Shape& shape) {
    std::cout << "  [runtime  dispatch]     "
              << shape.name()
              << " | area = "      << shape.area()
              << " | perimeter = " << shape.perimeter()
              << '\n';
}

int main() {
    using namespace CMakeSandbox;

    std::cout << "=== " << version_string << " – Shapes Demo ===\n\n";

    // ------------------------------------------------------------------
    // 1. Compile-time polymorphism via concepts
    // ------------------------------------------------------------------
    std::cout << "-- Compile-time polymorphism (Shape2D concept) --\n";

    const geo::shapes::Circle    c{5.0};
    const geo::shapes::Rectangle r{4.0, 3.0};
    const geo::shapes::Triangle  t{3.0, 4.0, 5.0};

    describe(c);
    describe(r);
    describe(t);

    // generic algorithm using span of a single homogeneous type
    const std::array<geo::shapes::Circle, 3> circles{
        geo::shapes::Circle{1.0},
        geo::shapes::Circle{2.0},
        geo::shapes::Circle{3.0}
    };
    const double total = CMakeSandbox::math::total_area<geo::shapes::Circle>(circles);
    std::cout << "\n  total area of three circles = " << total << "\n\n";

    // ------------------------------------------------------------------
    // 2. Runtime polymorphism via virtual dispatch
    // ------------------------------------------------------------------
    std::cout << "-- Runtime polymorphism (virtual dispatch) --\n";

    std::vector<std::unique_ptr<geo::shapes::Shape>> polymorphic;
    polymorphic.push_back(std::make_unique<geo::shapes::Circle>(7.0));
    polymorphic.push_back(std::make_unique<geo::shapes::Rectangle>(6.0, 2.0));
    polymorphic.push_back(std::make_unique<geo::shapes::Triangle>(5.0, 12.0, 13.0));

    for (const auto& shape : polymorphic) {
        describe_runtime(*shape);
    }

    std::cout << "\nDone.\n";
    return 0;
}
