#include <CMakeSandbox/math/vec2d.hpp>

namespace sandbox::math {

std::ostream& operator<<(std::ostream& os, const Vec2d& v) {
    return os << '(' << v.m_x << ", " << v.m_y << ')';
}

} // namespace sandbox::math
