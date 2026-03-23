#pragma once

#include <CMakeSandbox/geo/shapes/shape.hpp>

namespace sandbox::geo {

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height);

    [[nodiscard]] double area()      const override;
    [[nodiscard]] double perimeter() const override;
    [[nodiscard]] double width()     const noexcept;
    [[nodiscard]] double height()    const noexcept;

private:
    double m_width;
    double m_height;
};

} // namespace sandbox::geo
