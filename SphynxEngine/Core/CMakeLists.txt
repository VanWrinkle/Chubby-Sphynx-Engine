add_library(Core KeyCodes.h log.cpp mouse.h SphynxCore.h MouseCodes.h)
target_compile_definitions( Core PUBLIC SPHYNX_DEBUG ) #Remove for release
target_include_directories(Core PUBLIC .)
target_link_libraries(Core PUBLIC spdlog glm glfw)
add_library(Engine::Core ALIAS Core)
