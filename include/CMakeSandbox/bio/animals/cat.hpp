#pragma once

#include <CMakeSandbox/bio/animals/animal.hpp>

namespace sandbox::bio {

class Cat final : public Animal {
public:
    explicit Cat(std::string name);
    [[nodiscard]] std::string sound() const override;
};

} // namespace sandbox::bio
