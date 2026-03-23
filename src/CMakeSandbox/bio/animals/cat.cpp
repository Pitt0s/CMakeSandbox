#include <CMakeSandbox/bio/animals/cat.hpp>

namespace sandbox::bio {

Cat::Cat(std::string name) : Animal{std::move(name)} {}

std::string Cat::sound() const { return "Meow"; }

} // namespace sandbox::bio
