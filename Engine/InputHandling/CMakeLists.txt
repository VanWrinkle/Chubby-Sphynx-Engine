add_library(InputHandling inputhandling.h key.cpp)
add_library(Engine::InputHandling ALIAS InputHandling)
target_include_directories(InputHandling PUBLIC .)
target_link_libraries(InputHandling PUBLIC glm glad glfw)