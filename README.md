# CMakeSandbox

A sandbox repository for exploring [The Pitchfork Layout (PFL)](https://joholl.github.io/pitchfork-website/) with **Separate Header Placement** for a modern C++20 / CMake 3.28+ project.

The primary goal is to prove out the CMake patterns needed before applying them to a large HPC C++ framework refactoring:
- Hierarchical library targets (`CMakeSandbox::geo::shapes`, …)
- Proper `PUBLIC` / `PRIVATE` / `INTERFACE` usage
- Install + `find_package()` / `FetchContent()` support
- Generator-expression-driven compiler and build-type flags
- CMake presets and workflows
- `clang-tidy` integration
- `Version.hpp` generated from a CMake template

---

## Project structure

```
CMakeSandbox/
├── .gitignore
├── .clang-tidy                 # clang-tidy configuration
├── CMakeLists.txt              # Top-level project (CMake 3.28, C++20)
├── CMakePresets.json           # Configure / build / test / workflow presets
├── LICENSE.md
├── README.md
│
├── cmake/
│   ├── CMakeSandboxConfig.cmake.in   # Package config template
│   ├── CompilerOptions.cmake         # cmsb_set_compiler_options() helper
│   └── Version.hpp.in                # Configured into build tree at configure time
│
├── extern/                     # External dependencies (git submodules)
│   └── .gitkeep
│
├── include/                    # Public headers – separate from sources (PFL)
│   └── CMakeSandbox/
│       ├── geo/shapes/         # Geometric shapes (runtime + compile-time polymorphism)
│       │   ├── concepts.hpp
│       │   ├── shape.hpp
│       │   ├── circle.hpp
│       │   ├── rectangle.hpp
│       │   └── triangle.hpp
│       ├── bio/animals/        # Animals (runtime polymorphism / virtual dispatch)
│       │   ├── animal.hpp
│       │   ├── dog.hpp
│       │   ├── cat.hpp
│       │   └── bird.hpp
│       └── math/               # Header-only math utilities (templates + concepts)
│           ├── vec2d.hpp
│           └── algorithms.hpp
│
├── src/
│   └── CMakeSandbox/
│       ├── CMakeLists.txt      # Umbrella INTERFACE targets (sandbox_geo, sandbox_bio)
│       ├── geo/shapes/
│       │   ├── CMakeLists.txt
│       │   ├── circle.cpp
│       │   ├── rectangle.cpp
│       │   └── triangle.cpp
│       ├── bio/animals/
│       │   ├── CMakeLists.txt
│       │   ├── animal.cpp
│       │   ├── dog.cpp
│       │   ├── cat.cpp
│       │   └── bird.cpp
│       └── math/
│           └── CMakeLists.txt  # INTERFACE target – no .cpp files
│
├── apps/
│   ├── CMakeLists.txt
│   ├── shapes_demo.cpp
│   ├── animals_demo.cpp
│   └── math_demo.cpp
│
└── tests/
    ├── CMakeLists.txt
    ├── test_shapes.cpp
    ├── test_animals.cpp
    ├── test_math.cpp
    └── test_version.cpp
```

---

## CMake targets

| CMake target                    | Type        | What it provides                              |
|---------------------------------|-------------|-----------------------------------------------|
| `CMakeSandbox::geo::shapes`     | SHARED lib  | `Circle`, `Rectangle`, `Triangle` + concepts  |
| `CMakeSandbox::geo`             | INTERFACE   | Alias grouping all geo targets                |
| `CMakeSandbox::bio::animals`    | SHARED lib  | `Dog`, `Cat`, `Bird`                          |
| `CMakeSandbox::bio`             | INTERFACE   | Alias grouping all bio targets                |
| `CMakeSandbox::math`            | INTERFACE   | `Vec2D<T>`, `Numeric` concept, algorithms     |
| `CMakeSandbox::version`         | INTERFACE   | Generated `version.hpp`                       |

---

## Quick start

### Prerequisites

- CMake ≥ 3.28
- A C++20 compiler (GCC 13+ or Clang 16+)
- Ninja (optional but used by the presets)

### Configure and build (using presets)

```bash
# GCC debug build
cmake --preset gcc-debug
cmake --build --preset gcc-debug

# Clang release build
cmake --preset clang-release
cmake --build --preset clang-release
```

### Run tests

```bash
ctest --preset gcc-debug
```

### Full workflow (configure → build → test for both compilers)

```bash
cmake --workflow --preset ci
```

### Install

```bash
cmake --build --preset gcc-release
cmake --install build/gcc-release --prefix /opt/CMakeSandbox
```

### Enable clang-tidy

```bash
cmake --preset clang-tidy
cmake --build --preset clang-tidy
```

---

## Using as a dependency

### Via `find_package()` (after install)

```cmake
find_package(CMakeSandbox REQUIRED)
target_link_libraries(my_app PRIVATE CMakeSandbox::geo::shapes)
```

### Via `FetchContent()`

```cmake
include(FetchContent)
FetchContent_Declare(CMakeSandbox
    GIT_REPOSITORY https://github.com/Pitt0s/CMakeSandbox.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(CMakeSandbox)
target_link_libraries(my_app PRIVATE CMakeSandbox::geo::shapes)
```

---

## C++ examples

### Runtime polymorphism (virtual dispatch)

```cpp
#include "CMakeSandbox/geo/shapes/circle.hpp"
#include "CMakeSandbox/geo/shapes/shape.hpp"

std::unique_ptr<CMakeSandbox::geo::shapes::Shape> s =
    std::make_unique<CMakeSandbox::geo::shapes::Circle>(5.0);
std::cout << s->name() << " area = " << s->area() << '\n';
```

### Compile-time polymorphism (C++20 concepts)

```cpp
#include "CMakeSandbox/geo/shapes/concepts.hpp"
#include "CMakeSandbox/geo/shapes/circle.hpp"

template <CMakeSandbox::geo::shapes::Shape2D S>
void describe(const S& shape) {
    std::cout << shape.name() << " area = " << shape.area() << '\n';
}

describe(CMakeSandbox::geo::shapes::Circle{3.0});   // no virtual call
```

### Header-only math (Vec2D + Numeric concept)

```cpp
#include "CMakeSandbox/math/vec2d.hpp"

CMakeSandbox::math::Vec2Dd a{3.0, 0.0}, b{0.0, 4.0};
std::cout << "dot  = " << a.dot(b)   << '\n';   // 0
std::cout << "len  = " << a.length() << '\n';   // 3
```

---

## Notes on Spack / EasyBuild / ReFrame / JUBE

This CMake structure is fully compatible with Spack and EasyBuild:
- The install layout follows `CMAKE_INSTALL_PREFIX/{bin,lib,include,lib/cmake/CMakeSandbox}`.
- A `CMakeSandboxConfig.cmake` is installed, so Spack packages can use `cmake_args = ["-DCMAKE_INSTALL_PREFIX=..."]` and downstream packages use `find_package(CMakeSandbox)`.
- ReFrame and JUBE test descriptions can invoke `ctest --preset <name>` or individual test executables directly.
