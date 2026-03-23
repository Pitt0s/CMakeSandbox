#include <CMakeSandbox/geo/shapes/circle.hpp>

#include <numbers>

namespace sandbox::geo {

Circle::Circle(double radius)
    : Shape{"Circle"}, m_radius{radius} {}

double Circle::area() const {
    return std::numbers::pi * m_radius * m_radius;
}

double Circle::perimeter() const {
    return 2.0 * std::numbers::pi * m_radius;
}

double Circle::radius() const noexcept { return m_radius; }

} // namespace sandbox::geo
