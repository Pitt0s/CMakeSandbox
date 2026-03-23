#include <CMakeSandbox/bio/animals/dog.hpp>

namespace sandbox::bio {

Dog::Dog(std::string name) : Animal{std::move(name)} {}

std::string Dog::sound() const { return "Woof"; }

} // namespace sandbox::bio
