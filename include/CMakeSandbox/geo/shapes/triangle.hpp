// include/CMakeSandbox/geo/shapes/triangle.hpp

#pragma once

#include "CMakeSandbox/geo/shapes/shape.hpp"

namespace CMakeSandbox::geo::shapes {

/// A triangle defined by its three side lengths (a, b, c).
class Triangle final : public Shape {
public:
    Triangle(double a, double b, double c);

    [[nodiscard]] double      area()        const override;
    [[nodiscard]] double      perimeter()   const override;
    [[nodiscard]] std::string name()        const override;

    [[nodiscard]] double side_a() const noexcept;
    [[nodiscard]] double side_b() const noexcept;
    [[nodiscard]] double side_c() const noexcept;

private:
    double a_, b_, c_;
};

} // namespace CMakeSandbox::geo::shapes
