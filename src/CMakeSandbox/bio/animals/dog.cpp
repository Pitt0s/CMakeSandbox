// src/CMakeSandbox/bio/animals/dog.cpp

#include "CMakeSandbox/bio/animals/dog.hpp"

namespace CMakeSandbox::bio::animals {

Dog::Dog(std::string_view name) : Animal(name) {}

std::string Dog::speak() const {
    return "Woof!";
}

std::string Dog::move() const {
    return "runs";
}

} // namespace CMakeSandbox::bio::animals
