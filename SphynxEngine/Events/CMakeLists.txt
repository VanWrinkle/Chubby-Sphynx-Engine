add_library(Events event.cpp event.h keyevent.h)
target_include_directories(Events PUBLIC .)
target_link_libraries(Events PUBLIC Engine::Core)
add_library(Engine::Events ALIAS Events)