#include <CMakeSandbox/geo/shapes/shape.hpp>

namespace sandbox::geo {

Shape::Shape(std::string name) : m_name{std::move(name)} {}

const std::string& Shape::name() const noexcept { return m_name; }

} // namespace sandbox::geo
