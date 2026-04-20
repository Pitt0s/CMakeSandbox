// include/CMakeSandbox/geo/shapes/rectangle.hpp

#pragma once

#include "CMakeSandbox/geo/shapes/shape.hpp"

namespace CMakeSandbox::geo::shapes {

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height);

    [[nodiscard]] double      area()        const override;
    [[nodiscard]] double      perimeter()   const override;
    [[nodiscard]] std::string name()        const override;
    [[nodiscard]] double      width()       const noexcept;
    [[nodiscard]] double      height()      const noexcept;

private:
    double width_;
    double height_;
};

} // namespace CMakeSandbox::geo::shapes
