// src/CMakeSandbox/geo/shapes/circle.cpp

#include "CMakeSandbox/geo/shapes/circle.hpp"

#include <numbers>
#include <string>

namespace CMakeSandbox::geo::shapes {

Circle::Circle(double radius) : radius_(radius) {}

double Circle::area() const {
    return std::numbers::pi * radius_ * radius_;
}

double Circle::perimeter() const {
    return 2.0 * std::numbers::pi * radius_;
}

std::string Circle::name() const {
    return "Circle";
}

double Circle::radius() const noexcept {
    return radius_;
}

} // namespace CMakeSandbox::geo::shapes
