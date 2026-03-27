// include/CMakeSandbox/bio/animals/bird.hpp

#pragma once

#include "CMakeSandbox/bio/animals/animal.hpp"

namespace CMakeSandbox::bio::animals {

class CMSB_EXPERIMENTAL Bird final : public Animal {
public:
    explicit Bird(std::string_view name);

    [[nodiscard]] std::string speak() const override;
    [[nodiscard]] std::string move()  const override;
};

} // namespace CMakeSandbox::bio::animals
