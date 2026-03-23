#pragma once

#include <CMakeSandbox/geo/shapes/shape.hpp>

namespace sandbox::geo {

class Triangle final : public Shape {
public:
    Triangle(double a, double b, double c);

    [[nodiscard]] double area()      const override;
    [[nodiscard]] double perimeter() const override;
    [[nodiscard]] double side_a()    const noexcept;
    [[nodiscard]] double side_b()    const noexcept;
    [[nodiscard]] double side_c()    const noexcept;

private:
    double m_a;
    double m_b;
    double m_c;
};

} // namespace sandbox::geo
