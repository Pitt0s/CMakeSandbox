add_executable(math_demo     math_demo.cpp)
add_executable(shapes_demo   shapes_demo.cpp)
add_executable(animals_demo  animals_demo.cpp)

target_include_directories(math_demo    PRIVATE "${CMAKE_BINARY_DIR}/include")
target_include_directories(shapes_demo  PRIVATE "${CMAKE_BINARY_DIR}/include")
target_include_directories(animals_demo PRIVATE "${CMAKE_BINARY_DIR}/include")

target_link_libraries(math_demo    PRIVATE CMakeSandbox::math)
target_link_libraries(shapes_demo  PRIVATE CMakeSandbox::geo::shapes)
target_link_libraries(animals_demo PRIVATE CMakeSandbox::bio::animals)
