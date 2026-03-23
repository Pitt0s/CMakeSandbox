#pragma once

#include <string>

namespace sandbox::bio {

class Animal {
public:
    explicit Animal(std::string name);
    virtual ~Animal() = default;

    Animal(const Animal&)            = default;
    Animal& operator=(const Animal&) = default;
    Animal(Animal&&)                 = default;
    Animal& operator=(Animal&&)      = default;

    [[nodiscard]] const std::string& name()  const noexcept;
    [[nodiscard]] virtual std::string sound() const = 0;

private:
    std::string m_name;
};

} // namespace sandbox::bio
