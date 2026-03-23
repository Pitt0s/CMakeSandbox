#include <CMakeSandbox/bio/animals/animal.hpp>

namespace sandbox::bio {

Animal::Animal(std::string name) : m_name{std::move(name)} {}

const std::string& Animal::name() const noexcept { return m_name; }

} // namespace sandbox::bio
