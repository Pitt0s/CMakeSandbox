// src/CMakeSandbox/geo/shapes/triangle.cpp

#include "CMakeSandbox/geo/shapes/triangle.hpp"

#include <cmath>
#include <string>

namespace CMakeSandbox::geo::shapes {

Triangle::Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}

double Triangle::area() const {
    // Heron's formula
    const double s = (a_ + b_ + c_) / 2.0;
    return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
}

double Triangle::perimeter() const {
    return a_ + b_ + c_;
}

std::string Triangle::name() const {
    return "Triangle";
}

double Triangle::side_a() const noexcept { return a_; }
double Triangle::side_b() const noexcept { return b_; }
double Triangle::side_c() const noexcept { return c_; }

} // namespace CMakeSandbox::geo::shapes
