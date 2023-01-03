add_library(Events Event.cpp Event.h KeyEvent.h MouseEvent.h)
target_include_directories(Events PUBLIC .)
target_link_libraries(Events PUBLIC Engine::Core)
add_library(Engine::Events ALIAS Events)