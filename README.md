# CMakeSandbox

**Version 0.1.0** · C++20 · CMake 3.26
<!-- When cutting a new release, update the version badge above and the GIT_TAG references in the FetchContent examples below. -->

A sandbox repository for exploring [The Pitchfork Layout (PFL)](https://joholl.github.io/pitchfork-website/) with **Separate Header Placement** for a modern C++20 / CMake 3.26 project.

The primary goal is to prove out the CMake patterns needed before applying them to a large HPC C++ framework refactoring:
- Hierarchical library targets (`CMakeSandbox::geo::shapes`, …)
- Proper `PUBLIC` / `PRIVATE` / `INTERFACE` usage
- Install + `find_package()` / `FetchContent()` support
- Generator-expression-driven compiler and build-type flags
- CMake presets and workflows
- `clang-tidy` integration
- `Version.hpp` generated from a CMake template
- **API-status tagging system** (`CMSB_SUPPORTED`, `CMSB_DEPRECATED`, `CMSB_EXPERIMENTAL`)

---

## Project structure

```
CMakeSandbox/
├── .gitignore
├── .clang-tidy                 # clang-tidy configuration
├── CMakeLists.txt              # Top-level project (CMake 3.26, C++20)
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
| `CMakeSandbox::api_status`      | INTERFACE   | `api_status.hpp` tagging macros               |

---

## API-status tagging system

`include/CMakeSandbox/api_status.hpp` provides three macros that annotate the
support status of public APIs.  Place each macro **after** the leading keyword
(`class`, `struct`, `void`, …):

```cpp
#include "CMakeSandbox/api_status.hpp"

class CMSB_SUPPORTED   Circle { … };   // stable, fully supported
class CMSB_EXPERIMENTAL Animal { … };  // may change; opt-in required
CMSB_DEPRECATED("Use print_shape_info() instead.") void print_info(…);
```

### Status levels

| Macro | Meaning | Compiler effect |
|---|---|---|
| `CMSB_SUPPORTED` | Stable, fully-supported API | Expands to nothing (documentation annotation) |
| `CMSB_EXPERIMENTAL` | May change without notice | Emits a `[[deprecated]]`-style warning at every use site |
| `CMSB_DEPRECATED("reason")` | Scheduled for removal | Emits a `[[deprecated("reason")]]` warning at every use site |

### Opting in to experimental APIs

The recommended approach is to pass the preprocessor macro via your build
system so it applies consistently across all translation units.

**CMake (preferred for FetchContent consumers):**

```cmake
set(CMSB_ENABLE_EXPERIMENTAL ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(CMakeSandbox)
target_link_libraries(my_app PRIVATE
    CMakeSandbox::api_status        # propagates CMSB_ENABLE_EXPERIMENTAL
    CMakeSandbox::bio::animals
)
```

**Compiler flag:**

```bash
g++ -DCMSB_ENABLE_EXPERIMENTAL …
```

**Per-translation-unit `#define` (use only when the above are not available):**
The macro must appear before the first CMakeSandbox header include in that file.

```cpp
#define CMSB_ENABLE_EXPERIMENTAL
#include "CMakeSandbox/bio/animals/dog.hpp"
```

### Silencing deprecated warnings only

```cpp
#define CMSB_NO_DEPRECATED_WARNINGS
#include "CMakeSandbox/math/algorithms.hpp"
```

### Current API-status map

| Component | Status |
|---|---|
| `CMakeSandbox::geo::shapes` – `Circle`, `Rectangle`, `Triangle`, `Shape` | **Supported** |
| `CMakeSandbox::math` – `Vec2D<T>`, `Numeric`, `max_area`, `total_area` | **Supported** |
| `CMakeSandbox::bio::animals` – `Animal`, `Dog`, `Cat`, `Bird` | **Experimental** |
| `CMakeSandbox::math::print_info` | **Deprecated** – use `print_shape_info()` |

---

## Quick start

### Prerequisites

- CMake 3.26 (minimum required; see [CMake version note](#cmake-version-note) below)
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

### Via `FetchContent` – user guide

`FetchContent` lets you pull CMakeSandbox directly from GitHub without a prior
install step. This section shows a complete, production-ready setup.

#### Minimal example

```cmake
cmake_minimum_required(VERSION 3.26)
project(MyApp)

include(FetchContent)
FetchContent_Declare(CMakeSandbox
    GIT_REPOSITORY https://github.com/Pitt0s/CMakeSandbox.git
    GIT_TAG        v0.1.0          # pin to a release tag, not "main"
    GIT_SHALLOW    TRUE            # fetch only the tagged commit
)
FetchContent_MakeAvailable(CMakeSandbox)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE CMakeSandbox::geo::shapes)
```

#### Disabling unneeded build artifacts

When CMakeSandbox is consumed as a library you almost certainly do not want
its demo apps or its test suite to be compiled inside your project. Disable
them via cache variables *before* calling `FetchContent_MakeAvailable`:

```cmake
set(CMSB_BUILD_APPS  OFF CACHE BOOL "" FORCE)
set(CMSB_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(CMakeSandbox)
```

#### Choosing shared vs. static linkage

CMakeSandbox honours the standard `BUILD_SHARED_LIBS` CMake variable.

```cmake
# CMakeSandbox defaults BUILD_SHARED_LIBS to ON; override here for static
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(CMakeSandbox)
```

#### Available targets after `FetchContent_MakeAvailable`

| Target                          | Type        | What it provides                              |
|---------------------------------|-------------|-----------------------------------------------|
| `CMakeSandbox::geo::shapes`     | SHARED lib  | `Circle`, `Rectangle`, `Triangle` + concepts  |
| `CMakeSandbox::geo`             | INTERFACE   | Umbrella – links all geo targets               |
| `CMakeSandbox::bio::animals`    | SHARED lib  | `Dog`, `Cat`, `Bird`                          |
| `CMakeSandbox::bio`             | INTERFACE   | Umbrella – links all bio targets               |
| `CMakeSandbox::math`            | INTERFACE   | `Vec2D<T>`, `Numeric` concept, algorithms     |
| `CMakeSandbox::version`         | INTERFACE   | Generated `version.hpp`                       |
| `CMakeSandbox::api_status`      | INTERFACE   | `api_status.hpp` tagging macros               |

#### Full consumer `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.26)
project(MyConsumerApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ── Fetch CMakeSandbox ────────────────────────────────────────────────────────
set(CMSB_BUILD_APPS  OFF CACHE BOOL "" FORCE)
set(CMSB_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON  CACHE BOOL "" FORCE)   # or OFF for static

FetchContent_Declare(CMakeSandbox
    GIT_REPOSITORY https://github.com/Pitt0s/CMakeSandbox.git
    GIT_TAG        v0.1.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(CMakeSandbox)

# ── Your application ──────────────────────────────────────────────────────────
add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE
    CMakeSandbox::geo::shapes   # geometric primitives
    CMakeSandbox::math          # header-only math utilities
)
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

## Migrating a large existing project to this structure

The patterns proven in this sandbox are intentionally simple so they can be
lifted into a large, pre-existing C++ project that is being refactored to PFL.
The key insight is **incremental migration**: you do not need to move everything
at once.

### Step 1 – Introduce the directory skeleton alongside the old layout

Create the `include/`, `src/`, `apps/`, `tests/` and `cmake/` directories next
to the existing source tree.  Keep the old build system working during the
migration so the project stays green on CI.

```
myproject/
├── old_src/        ← untouched for now
├── include/        ← new PFL public headers go here
├── src/            ← new PFL compiled sources go here
└── cmake/          ← CompilerOptions.cmake, config template, …
```

### Step 2 – Pick one subsystem and migrate it first

Choose the smallest, most self-contained subsystem (a utility library, a math
module, etc.) and move its headers into `include/<Project>/<subsystem>/` and
its `.cpp` files into `src/<Project>/<subsystem>/`.  Write a new
`CMakeLists.txt` for it following this sandbox's pattern:

```cmake
add_library(myproject_math)
add_library(MyProject::math ALIAS myproject_math)

# Sources and public headers declared together via FILE_SET (CMake ≥ 3.23).
# BASE_DIRS defines the include root; FILE_SET automatically populates
# INTERFACE_INCLUDE_DIRECTORIES – no target_include_directories() call needed.
target_sources(myproject_math
    PRIVATE
        vec2d.cpp
    PUBLIC
        FILE_SET myproject_math_headers
        TYPE HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/MyProject/math/vec2d.hpp"
)

target_link_libraries(myproject_math
    PRIVATE MyProject::compiler_flags
)
```

### Step 3 – Create INTERFACE umbrella targets immediately

Even when only one subsystem has been migrated, create the umbrella
`MyProject::math`, `MyProject::geo`, … targets.  Consumers in the old part of
the codebase can start linking against `MyProject::math` without knowing the
internal target names, making future splits invisible to them.

### Step 4 – Replace old `#include` paths incrementally

Update `#include` directives one translation unit at a time to use the new
`include/<Project>/…` paths.  A CI step that compiles both the old and new
targets in parallel catches regressions early.

### Step 5 – Move remaining subsystems

Repeat Step 2–4 for each subsystem.  Before publishing a release, verify
downstream integration with `FetchContent_Declare` pointing `SOURCE_DIR` at
your local checkout.  This exercises the full FetchContent path without
needing a prior `cmake --install`:

```cmake
cmake_minimum_required(VERSION 3.26)
project(MyConsumerApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Disable the library's own apps and tests when consumed as a dependency.
set(CMSB_BUILD_APPS  OFF CACHE BOOL "" FORCE)
set(CMSB_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(MyProject
    SOURCE_DIR /path/to/myproject   # local checkout; replace with GIT_REPOSITORY for CI
)
FetchContent_MakeAvailable(MyProject)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE MyProject::math)
```

The sandbox ships a ready-made consumer in `tests/smoke/` that demonstrates
both the `FetchContent SOURCE_DIR` and `find_package` patterns and is wired
into CI via the `smoke-gcc-debug` workflow preset (see
[Validate the install tree](#validate-the-install-tree) below).

### Tips for large HPC frameworks

- **Keep one `cmake/CompilerOptions.cmake`** that is the single source of truth
  for warning and optimisation flags.  Never sprinkle `target_compile_options`
  calls across leaf `CMakeLists.txt` files.
- **Use `PRIVATE` linkage for implementation details.**  If a library `A` uses
  `Boost.Filesystem` internally but exposes none of it in its public API, link
  Boost `PRIVATE`.  This prevents accidental transitive linkage in downstream
  targets.
- **Generate a `Version.hpp`** early (see `cmake/Version.hpp.in` in this
  sandbox).  It gives every component a single, CMake-driven source of version
  truth and is trivial to extend with build metadata.
- **Add `CMakePresets.json`** from the start.  Presets capture the full
  configure/build/test matrix (compilers, build types, static vs. shared) and
  make CI pipelines reproducible on developer workstations.  The CI workflow in
  `.github/workflows/ci.yml` runs every preset via `cmake --workflow` so the
  same commands work locally and on GitHub Actions.
- **Pin external dependencies** in `FetchContent_Declare` to a commit SHA or
  release tag, never to `main`/`master`, to keep builds reproducible across
  machines and over time.
- <a name="validate-the-install-tree"></a>**Validate the install tree** with the `tests/smoke/` consumer project
  included in this sandbox.  It can be driven in two ways:

  ```bash
  # 1. find_package mode – validates all install() rules are correct
  cmake --workflow --preset smoke-gcc-debug

  # 2. FetchContent SOURCE_DIR mode (manual, no prior install needed)
  cmake -S tests/smoke -B build/smoke \
        -DSMOKE_USE_FETCHCONTENT=ON \
        -DCMSB_SOURCE_DIR=$(pwd)
  cmake --build build/smoke
  ctest --test-dir build/smoke --output-on-failure
  ```

  The `smoke-gcc-debug` workflow preset runs
  **configure → build → install → smoke tests** in the correct order so both
  `smoke_find_package` and `smoke_fetchcontent` CTest tests are exercised.
  This catches missing `install()` rules, broken `CMakeSandboxConfig.cmake`
  aliases, or missing headers far earlier than a downstream consumer would.

---

## CMake version note

The minimum required version is **3.26**.  This is the lowest version that
provides all features used unconditionally in this project:

| Feature | Minimum CMake version |
|---|---|
| `cmake_minimum_required` / `project()` basics | 2.6 |
| `GNUInstallDirs`, `CMakePackageConfigHelpers` | 3.0 |
| Generator expressions (`$<CXX_COMPILER_ID:…>`) | 3.0 |
| `write_basic_package_version_file` | 3.14 |
| CMakePresets.json schema version 6 | 3.25 |
| `CMAKE_CXX_SCAN_FOR_MODULES` *(optional, guarded)* | 3.28 |

`CMAKE_CXX_SCAN_FOR_MODULES` is set only when running CMake 3.28 or later
(guarded by a `CMAKE_VERSION VERSION_GREATER_EQUAL "3.28"` check).  On CMake
3.26 and 3.27 this variable does not exist; named-module scanning is simply
not enabled by those versions, so no guard is needed on the consumer side.

---

## Notes on Spack / EasyBuild / ReFrame / JUBE

This CMake structure is fully compatible with Spack and EasyBuild:
- The install layout follows `CMAKE_INSTALL_PREFIX/{bin,lib,include,lib/cmake/CMakeSandbox}`.
- A `CMakeSandboxConfig.cmake` is installed, so Spack packages can use `cmake_args = ["-DCMAKE_INSTALL_PREFIX=..."]` and downstream packages use `find_package(CMakeSandbox)`.
- ReFrame and JUBE test descriptions can invoke `ctest --preset <name>` or individual test executables directly.
