// src/CMakeSandbox/bio/animals/cat.cpp

#include "CMakeSandbox/bio/animals/cat.hpp"

namespace CMakeSandbox::bio::animals {

Cat::Cat(std::string_view name) : Animal(name) {}

std::string Cat::speak() const {
    return "Meow!";
}

std::string Cat::move() const {
    return "sneaks";
}

} // namespace CMakeSandbox::bio::animals
