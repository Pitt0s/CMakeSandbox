// include/CMakeSandbox/bio/animals/dog.hpp

#pragma once

#include "CMakeSandbox/bio/animals/animal.hpp"

namespace CMakeSandbox::bio::animals {

class Dog final : public Animal {
public:
    explicit Dog(std::string_view name);

    [[nodiscard]] std::string speak() const override;
    [[nodiscard]] std::string move()  const override;
};

} // namespace CMakeSandbox::bio::animals
