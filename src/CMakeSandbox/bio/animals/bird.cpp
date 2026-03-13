// src/CMakeSandbox/bio/animals/bird.cpp

#include "CMakeSandbox/bio/animals/bird.hpp"

namespace CMakeSandbox::bio::animals {

Bird::Bird(std::string_view name) : Animal(name) {}

std::string Bird::speak() const {
    return "Tweet!";
}

std::string Bird::move() const {
    return "flies";
}

} // namespace CMakeSandbox::bio::animals
