// apps/animals_demo.cpp
//
// Demonstrates runtime polymorphism through the Animal hierarchy.

#include "CMakeSandbox/bio/animals/bird.hpp"
#include "CMakeSandbox/bio/animals/cat.hpp"
#include "CMakeSandbox/bio/animals/dog.hpp"
#include "CMakeSandbox/version.hpp"

#include <iostream>
#include <memory>
#include <vector>

void introduce(const CMakeSandbox::bio::animals::Animal& animal) {
    std::cout << "  " << animal.name()
              << " says \"" << animal.speak() << "\""
              << " and " << animal.move() << ".\n";
}

int main() {
    using namespace CMakeSandbox::bio::animals;

    std::cout << "=== " << CMakeSandbox::version_string
              << " – Animals Demo ===\n\n";

    // Build a heterogeneous collection of animals (runtime polymorphism)
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Rex"));
    zoo.push_back(std::make_unique<Cat>("Whiskers"));
    zoo.push_back(std::make_unique<Bird>("Tweety"));
    zoo.push_back(std::make_unique<Dog>("Buddy"));
    zoo.push_back(std::make_unique<Cat>("Shadow"));

    std::cout << "Our zoo has " << zoo.size() << " animals:\n";
    for (const auto& animal : zoo) {
        introduce(*animal);
    }

    std::cout << "\nDone.\n";
    return 0;
}
