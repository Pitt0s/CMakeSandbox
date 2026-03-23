#include <iostream>

#include <CMakeSandbox/geo/shapes/circle.hpp>
#include <CMakeSandbox/geo/shapes/rectangle.hpp>
#include <CMakeSandbox/geo/shapes/triangle.hpp>

int main() {
    using namespace sandbox::geo;

    Circle    c{5.0};
    Rectangle r{4.0, 6.0};
    Triangle  t{3.0, 4.0, 5.0};

    for (const Shape* s : {static_cast<const Shape*>(&c),
                           static_cast<const Shape*>(&r),
                           static_cast<const Shape*>(&t)}) {
        std::cout << s->name()
                  << ": area=" << s->area()
                  << " perimeter=" << s->perimeter()
                  << '\n';
    }

    return 0;
}
