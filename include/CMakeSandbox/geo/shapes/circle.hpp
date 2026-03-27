// include/CMakeSandbox/geo/shapes/circle.hpp

#pragma once

#include "CMakeSandbox/geo/shapes/shape.hpp"

namespace CMakeSandbox::geo::shapes {

class CMSB_SUPPORTED Circle final : public Shape {
public:
    explicit Circle(double radius);

    [[nodiscard]] double      area()        const override;
    [[nodiscard]] double      perimeter()   const override;
    [[nodiscard]] std::string name()        const override;
    [[nodiscard]] double      radius()      const noexcept;

private:
    double radius_;
};

} // namespace CMakeSandbox::geo::shapes
