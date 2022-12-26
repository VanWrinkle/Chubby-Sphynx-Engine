add_library(Core key.cpp log.cpp mouse.h sphynxcore.h)
target_compile_definitions( Core PUBLIC SPHYNX_DEBUG ) #Remove for release
target_include_directories(Core PUBLIC .)
target_link_libraries(Core PUBLIC spdlog glm glfw)
add_library(Engine::Core ALIAS Core)
