#include <CMakeSandbox/bio/animals/bird.hpp>

namespace sandbox::bio {

Bird::Bird(std::string name) : Animal{std::move(name)} {}

std::string Bird::sound() const { return "Tweet"; }

} // namespace sandbox::bio
