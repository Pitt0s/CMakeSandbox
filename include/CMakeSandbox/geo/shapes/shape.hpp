#pragma once

#include <string>

namespace sandbox::geo {

class Shape {
public:
    explicit Shape(std::string name);
    virtual ~Shape() = default;

    Shape(const Shape&)            = default;
    Shape& operator=(const Shape&) = default;
    Shape(Shape&&)                 = default;
    Shape& operator=(Shape&&)      = default;

    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] virtual double     area()      const = 0;
    [[nodiscard]] virtual double     perimeter() const = 0;

private:
    std::string m_name;
};

} // namespace sandbox::geo
