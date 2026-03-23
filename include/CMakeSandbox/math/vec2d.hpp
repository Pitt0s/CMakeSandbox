#pragma once

#include <ostream>

namespace sandbox::math {

class Vec2d {
public:
    constexpr Vec2d(double x, double y) noexcept : m_x{x}, m_y{y} {}

    [[nodiscard]] constexpr double x() const noexcept { return m_x; }
    [[nodiscard]] constexpr double y() const noexcept { return m_y; }

    [[nodiscard]] constexpr Vec2d operator+(const Vec2d& rhs) const noexcept {
        return {m_x + rhs.m_x, m_y + rhs.m_y};
    }
    [[nodiscard]] constexpr Vec2d operator-(const Vec2d& rhs) const noexcept {
        return {m_x - rhs.m_x, m_y - rhs.m_y};
    }
    [[nodiscard]] constexpr Vec2d operator*(double scalar) const noexcept {
        return {m_x * scalar, m_y * scalar};
    }

    [[nodiscard]] constexpr bool operator==(const Vec2d&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Vec2d& v);

private:
    double m_x;
    double m_y;
};

} // namespace sandbox::math
