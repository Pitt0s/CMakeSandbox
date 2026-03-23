// tests/test_version.cpp
//
// Tests for the generated version header.

#include "CMakeSandbox/version.hpp"

#include <cassert>
#include <iostream>

int main() {
    std::cout << "=== test_version ===\n";

    // Version numbers must be non-negative
    static_assert(CMakeSandbox::version_major >= 0);
    static_assert(CMakeSandbox::version_minor >= 0);
    static_assert(CMakeSandbox::version_patch >= 0);

    assert(!CMakeSandbox::version_string.empty());
    assert(!CMakeSandbox::project_name.empty());
    assert(CMakeSandbox::project_name == "CMakeSandbox");

    std::cout << "  project     : " << CMakeSandbox::project_name    << '\n';
    std::cout << "  version     : " << CMakeSandbox::version_string  << '\n';
    std::cout << "  major       : " << CMakeSandbox::version_major   << '\n';
    std::cout << "  minor       : " << CMakeSandbox::version_minor   << '\n';
    std::cout << "  patch       : " << CMakeSandbox::version_patch   << '\n';

    // Build metadata checks
    assert(!CMakeSandbox::build_info::compiler_id.empty());
    assert(!CMakeSandbox::build_info::compiler_version.empty());
    static_assert(CMakeSandbox::build_info::cxx_standard == 20);

    std::cout << "  compiler    : " << CMakeSandbox::build_info::compiler_id
                                    << ' ' << CMakeSandbox::build_info::compiler_version << '\n';
    std::cout << "  build_type  : " << CMakeSandbox::build_info::build_type   << '\n';
    std::cout << "  cxx_standard: " << CMakeSandbox::build_info::cxx_standard << '\n';
    std::cout << "  cxx_flags   : \"" << CMakeSandbox::build_info::cxx_flags  << "\"\n";

    std::cout << "  [PASS] version header\n";
    std::cout << "All version tests passed.\n";
    return 0;
}
