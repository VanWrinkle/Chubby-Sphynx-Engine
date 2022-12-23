add_library(Logging log.h log.cpp)
target_include_directories(Logging PUBLIC .)
target_link_libraries(Logging PUBLIC spdlog)
add_library(Engine::Logging ALIAS Logging)
