#include <CMakeSandbox/geo/shapes/rectangle.hpp>

namespace sandbox::geo {

Rectangle::Rectangle(double width, double height)
    : Shape{"Rectangle"}, m_width{width}, m_height{height} {}

double Rectangle::area()      const { return m_width * m_height; }
double Rectangle::perimeter() const { return 2.0 * (m_width + m_height); }
double Rectangle::width()     const noexcept { return m_width; }
double Rectangle::height()    const noexcept { return m_height; }

} // namespace sandbox::geo
