// src/CMakeSandbox/bio/animals/animal.cpp

#include "CMakeSandbox/bio/animals/animal.hpp"

namespace CMakeSandbox::bio::animals {

Animal::Animal(std::string_view name) : name_(name) {}

const std::string& Animal::name() const noexcept {
    return name_;
}

} // namespace CMakeSandbox::bio::animals
