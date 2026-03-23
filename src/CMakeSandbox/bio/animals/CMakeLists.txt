add_library(sandbox_bio_animals SHARED
    animal.cpp
    bird.cpp
    cat.cpp
    dog.cpp
)

add_library(CMakeSandbox::bio::animals ALIAS sandbox_bio_animals)

target_include_directories(sandbox_bio_animals
    PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
)

set_target_properties(sandbox_bio_animals PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
