#include <CMakeSandbox/geo/shapes/triangle.hpp>

#include <cmath>

namespace sandbox::geo {

Triangle::Triangle(double a, double b, double c)
    : Shape{"Triangle"}, m_a{a}, m_b{b}, m_c{c} {}

double Triangle::area() const {
    const double s = (m_a + m_b + m_c) / 2.0;
    return std::sqrt(s * (s - m_a) * (s - m_b) * (s - m_c));
}

double Triangle::perimeter() const { return m_a + m_b + m_c; }
double Triangle::side_a()    const noexcept { return m_a; }
double Triangle::side_b()    const noexcept { return m_b; }
double Triangle::side_c()    const noexcept { return m_c; }

} // namespace sandbox::geo
