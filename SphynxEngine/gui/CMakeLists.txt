add_library(sphynx_gui gui_core.cpp gui_core.h)
target_link_libraries(sphynx_gui PRIVATE ImGui glfw glad)
target_include_directories(sphynx_gui PUBLIC .)

add_library(Engine::Gui ALIAS sphynx_gui)