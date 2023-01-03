add_library(Math sphynxmath.cpp sphynxmath.h)
add_library(Engine::Math ALIAS Math)
target_link_libraries(Math PUBLIC glm)
target_include_directories(Math PUBLIC .)
