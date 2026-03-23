add_library(sandbox_math SHARED
    vec2d.cpp
)

add_library(CMakeSandbox::math ALIAS sandbox_math)

target_include_directories(sandbox_math
    PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
)

set_target_properties(sandbox_math PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
