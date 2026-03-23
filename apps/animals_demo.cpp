#include <iostream>

#include <CMakeSandbox/bio/animals/bird.hpp>
#include <CMakeSandbox/bio/animals/cat.hpp>
#include <CMakeSandbox/bio/animals/dog.hpp>

int main() {
    using namespace sandbox::bio;

    Bird bird{"Tweety"};
    Cat  cat{"Whiskers"};
    Dog  dog{"Rex"};

    for (const Animal* a : {static_cast<const Animal*>(&bird),
                            static_cast<const Animal*>(&cat),
                            static_cast<const Animal*>(&dog)}) {
        std::cout << a->name() << " says: " << a->sound() << '\n';
    }

    return 0;
}
