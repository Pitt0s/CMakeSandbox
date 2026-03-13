// include/CMakeSandbox/geo/shapes/concepts.hpp
//
// Compile-time concepts for 2-D shapes.
// Any type satisfying Shape2D can be used with the generic algorithms below
// without any runtime overhead (static duck-typing).

#pragma once

#include <concepts>
#include <string>

namespace CMakeSandbox::geo::shapes {

/// A type models Shape2D if it exposes area(), perimeter() and name().
template <typename T>
concept Shape2D = requires(const T& s) {
    { s.area()      } -> std::convertible_to<double>;
    { s.perimeter() } -> std::convertible_to<double>;
    { s.name()      } -> std::convertible_to<std::string>;
};

} // namespace CMakeSandbox::geo::shapes
