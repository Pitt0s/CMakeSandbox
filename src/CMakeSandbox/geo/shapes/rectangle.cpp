// src/CMakeSandbox/geo/shapes/rectangle.cpp

#include "CMakeSandbox/geo/shapes/rectangle.hpp"

#include <string>

namespace CMakeSandbox::geo::shapes {

Rectangle::Rectangle(double width, double height)
    : width_(width), height_(height) {}

double Rectangle::area() const {
    return width_ * height_;
}

double Rectangle::perimeter() const {
    return 2.0 * (width_ + height_);
}

std::string Rectangle::name() const {
    return "Rectangle";
}

double Rectangle::width() const noexcept {
    return width_;
}

double Rectangle::height() const noexcept {
    return height_;
}

} // namespace CMakeSandbox::geo::shapes
