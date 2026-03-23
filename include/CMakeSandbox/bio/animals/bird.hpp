#pragma once

#include <CMakeSandbox/bio/animals/animal.hpp>

namespace sandbox::bio {

class Bird final : public Animal {
public:
    explicit Bird(std::string name);
    [[nodiscard]] std::string sound() const override;
};

} // namespace sandbox::bio
