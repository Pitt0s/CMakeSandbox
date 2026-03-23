#include <cassert>
#include <iostream>

#include <CMakeSandbox/bio/animals/bird.hpp>
#include <CMakeSandbox/bio/animals/cat.hpp>
#include <CMakeSandbox/bio/animals/dog.hpp>

int main() {
    using namespace sandbox::bio;

    Bird bird{"Tweety"};
    assert(bird.name()  == "Tweety");
    assert(bird.sound() == "Tweet");

    Cat cat{"Whiskers"};
    assert(cat.name()  == "Whiskers");
    assert(cat.sound() == "Meow");

    Dog dog{"Rex"};
    assert(dog.name()  == "Rex");
    assert(dog.sound() == "Woof");

    std::cout << "test_animals PASSED\n";
    return 0;
}
