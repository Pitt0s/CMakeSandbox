#include <cassert>
#include <iostream>

#include <CMakeSandbox/version.hpp>

int main() {
    assert(sandbox::version_major >= 0);
    assert(sandbox::version_minor >= 0);
    assert(sandbox::version_patch >= 0);
    assert(!sandbox::version_string.empty());

    std::cout << "Version: " << sandbox::version_string << '\n';
    std::cout << "test_version PASSED\n";
    return 0;
}
