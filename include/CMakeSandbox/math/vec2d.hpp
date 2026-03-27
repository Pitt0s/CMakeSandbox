// include/CMakeSandbox/math/vec2d.hpp
//
// Header-only 2-D vector template.
// Demonstrates compile-time polymorphism via templates and C++20 concepts.

#pragma once

#include "CMakeSandbox/api_status.hpp"

#include <concepts>
#include <cmath>
#include <ostream>
#include <type_traits>

namespace CMakeSandbox::math {

// ---------------------------------------------------------------------------
// Concept
// ---------------------------------------------------------------------------

/// Numeric concept: any arithmetic type (int, float, double, …).
template <typename T>
concept CMSB_SUPPORTED Numeric = std::is_arithmetic_v<T>;

// ---------------------------------------------------------------------------
// Vec2D<T>
// ---------------------------------------------------------------------------

template <Numeric T>
class CMSB_SUPPORTED Vec2D {
public:
    T x{};
    T y{};

    constexpr Vec2D() noexcept = default;
    constexpr Vec2D(T x_, T y_) noexcept : x(x_), y(y_) {}

    // Arithmetic operators
    [[nodiscard]] constexpr Vec2D operator+(const Vec2D& rhs) const noexcept {
        return {x + rhs.x, y + rhs.y};
    }
    [[nodiscard]] constexpr Vec2D operator-(const Vec2D& rhs) const noexcept {
        return {x - rhs.x, y - rhs.y};
    }
    [[nodiscard]] constexpr Vec2D operator*(T scalar) const noexcept {
        return {x * scalar, y * scalar};
    }

    // Dot product
    [[nodiscard]] constexpr T dot(const Vec2D& rhs) const noexcept {
        return x * rhs.x + y * rhs.y;
    }

    // 2-D "cross product" (scalar z-component of the 3-D cross product)
    [[nodiscard]] constexpr T cross(const Vec2D& rhs) const noexcept {
        return x * rhs.y - y * rhs.x;
    }

    // Euclidean length
    [[nodiscard]] double length() const noexcept {
        return std::sqrt(static_cast<double>(x) * static_cast<double>(x)
                       + static_cast<double>(y) * static_cast<double>(y));
    }

    // Equality
    [[nodiscard]] constexpr bool operator==(const Vec2D&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Vec2D& v) {
        return os << '(' << v.x << ", " << v.y << ')';
    }
};

// Scalar * Vec2D (commutative)
template <Numeric T>
[[nodiscard]] constexpr Vec2D<T> operator*(T scalar, const Vec2D<T>& v) noexcept {
    return v * scalar;
}

// Convenient aliases
using Vec2Di = Vec2D<int>;
using Vec2Df = Vec2D<float>;
using Vec2Dd = Vec2D<double>;

} // namespace CMakeSandbox::math
