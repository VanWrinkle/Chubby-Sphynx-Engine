
add_library(GLFWApplication GLFWApplication.h GLFWApplication.cpp)
add_library(Engine::GLFWApplication ALIAS GLFWApplication)
target_include_directories(GLFWApplication PUBLIC .)
target_link_libraries(GLFWApplication glad glfw TCLAP)
