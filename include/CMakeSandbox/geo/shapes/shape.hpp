// include/CMakeSandbox/geo/shapes/shape.hpp
//
// Abstract base class for runtime-polymorphic 2-D shapes.

#pragma once

#include "CMakeSandbox/api_status.hpp"

#include <string>

namespace CMakeSandbox::geo::shapes {

/// Abstract base class – models the OOP (runtime) polymorphism side.
class CMSB_SUPPORTED Shape {
public:
    Shape()                          = default;
    Shape(const Shape&)              = default;
    Shape(Shape&&)                   = default;
    Shape& operator=(const Shape&)   = default;
    Shape& operator=(Shape&&)        = default;
    virtual ~Shape()                 = default;

    [[nodiscard]] virtual double      area()      const = 0;
    [[nodiscard]] virtual double      perimeter() const = 0;
    [[nodiscard]] virtual std::string name()      const = 0;
};

} // namespace CMakeSandbox::geo::shapes
