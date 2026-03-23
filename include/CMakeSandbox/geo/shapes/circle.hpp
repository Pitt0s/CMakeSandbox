#pragma once

#include <CMakeSandbox/geo/shapes/shape.hpp>

namespace sandbox::geo {

class Circle final : public Shape {
public:
    explicit Circle(double radius);

    [[nodiscard]] double area()      const override;
    [[nodiscard]] double perimeter() const override;
    [[nodiscard]] double radius()    const noexcept;

private:
    double m_radius;
};

} // namespace sandbox::geo
