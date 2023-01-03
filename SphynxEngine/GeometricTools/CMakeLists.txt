
add_library(GeometricTools INTERFACE GeometricTools.h)
target_link_libraries(GeometricTools INTERFACE glm)
add_library(Engine::GeometricTools ALIAS GeometricTools)
target_include_directories(GeometricTools INTERFACE .)
