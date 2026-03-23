#pragma once

#include <CMakeSandbox/bio/animals/animal.hpp>

namespace sandbox::bio {

class Dog final : public Animal {
public:
    explicit Dog(std::string name);
    [[nodiscard]] std::string sound() const override;
};

} // namespace sandbox::bio
