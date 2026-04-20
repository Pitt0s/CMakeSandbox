// include/CMakeSandbox/bio/animals/animal.hpp
//
// Abstract base class for runtime-polymorphic animals.

#pragma once

#include <string>
#include <string_view>

namespace CMakeSandbox::bio::animals {

class Animal {
public:
    explicit Animal(std::string_view name);
    Animal(const Animal&)              = default;
    Animal(Animal&&)                   = default;
    Animal& operator=(const Animal&)   = default;
    Animal& operator=(Animal&&)        = default;
    virtual ~Animal()                  = default;

    /// Returns a sound the animal makes.
    [[nodiscard]] virtual std::string speak() const = 0;

    /// Returns a description of how the animal moves.
    [[nodiscard]] virtual std::string move()  const = 0;

    [[nodiscard]] const std::string& name() const noexcept;

private:
    std::string name_;
};

} // namespace CMakeSandbox::bio::animals
