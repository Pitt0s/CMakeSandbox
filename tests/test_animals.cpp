// tests/test_animals.cpp
//
// Tests for the bio::animals library.

#include "CMakeSandbox/bio/animals/bird.hpp"
#include "CMakeSandbox/bio/animals/cat.hpp"
#include "CMakeSandbox/bio/animals/dog.hpp"

#include <cassert>
#include <iostream>
#include <memory>

namespace animals = CMakeSandbox::bio::animals;

static void test_dog() {
    const animals::Dog dog{"Rex"};
    assert(dog.name()  == "Rex");
    assert(dog.speak() == "Woof!");
    assert(dog.move()  == "runs");
    std::cout << "  [PASS] Dog\n";
}

static void test_cat() {
    const animals::Cat cat{"Whiskers"};
    assert(cat.name()  == "Whiskers");
    assert(cat.speak() == "Meow!");
    assert(cat.move()  == "sneaks");
    std::cout << "  [PASS] Cat\n";
}

static void test_bird() {
    const animals::Bird bird{"Tweety"};
    assert(bird.name()  == "Tweety");
    assert(bird.speak() == "Tweet!");
    assert(bird.move()  == "flies");
    std::cout << "  [PASS] Bird\n";
}

static void test_virtual_dispatch() {
    std::unique_ptr<animals::Animal> animal =
        std::make_unique<animals::Dog>("Buddy");
    assert(animal->name()  == "Buddy");
    assert(animal->speak() == "Woof!");

    animal = std::make_unique<animals::Cat>("Luna");
    assert(animal->name()  == "Luna");
    assert(animal->speak() == "Meow!");

    std::cout << "  [PASS] Virtual dispatch (polymorphic pointer)\n";
}

int main() {
    std::cout << "=== test_animals ===\n";
    test_dog();
    test_cat();
    test_bird();
    test_virtual_dispatch();
    std::cout << "All animal tests passed.\n";
    return 0;
}
