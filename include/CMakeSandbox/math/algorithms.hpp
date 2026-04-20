// include/CMakeSandbox/math/algorithms.hpp
//
// Generic algorithms that work with any type satisfying the Shape2D concept.
// Also includes generic container helpers using ranges (C++20).

#pragma once

#include "CMakeSandbox/geo/shapes/concepts.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <vector>

namespace CMakeSandbox::math {

/// Print a formatted summary for any Shape2D value.
template <CMakeSandbox::geo::shapes::Shape2D S>
void print_shape_info(const S& shape) {
    std::cout << shape.name()
              << " | area = "      << shape.area()
              << " | perimeter = " << shape.perimeter()
              << '\n';
}

/// Return a reference to the shape with the largest area in [first, last).
template <CMakeSandbox::geo::shapes::Shape2D S>
[[nodiscard]] const S& max_area(std::span<const S> shapes) {
    return *std::ranges::max_element(shapes,
        [](const S& a, const S& b) { return a.area() < b.area(); });
}

/// Compute the total area of all shapes in the range.
template <CMakeSandbox::geo::shapes::Shape2D S>
[[nodiscard]] double total_area(std::span<const S> shapes) {
    double sum = 0.0;
    for (const auto& s : shapes) {
        sum += s.area();
    }
    return sum;
}

} // namespace CMakeSandbox::math
