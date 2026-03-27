// include/CMakeSandbox/bio/animals/cat.hpp

#pragma once

#include "CMakeSandbox/bio/animals/animal.hpp"

namespace CMakeSandbox::bio::animals {

class CMSB_EXPERIMENTAL Cat final : public Animal {
public:
    explicit Cat(std::string_view name);

    [[nodiscard]] std::string speak() const override;
    [[nodiscard]] std::string move()  const override;
};

} // namespace CMakeSandbox::bio::animals
