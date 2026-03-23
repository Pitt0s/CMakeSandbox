add_library(sandbox_geo_shapes SHARED
    shape.cpp
    circle.cpp
    rectangle.cpp
    triangle.cpp
)

add_library(CMakeSandbox::geo::shapes ALIAS sandbox_geo_shapes)

target_include_directories(sandbox_geo_shapes
    PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
)

set_target_properties(sandbox_geo_shapes PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
