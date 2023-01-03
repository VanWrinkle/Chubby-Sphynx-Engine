
add_library(SphynxApplication SphynxApplication.h SphynxApplication.cpp)
add_library(Engine::SphynxApplication ALIAS SphynxApplication)
target_include_directories(SphynxApplication PUBLIC .)
target_link_libraries(SphynxApplication glad glfw TCLAP Engine::Core)
