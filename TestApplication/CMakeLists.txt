project(ChubbyEngineAppTest)

add_library(TestApplication
        gamegrid.h
        TestApplication.cpp
        )
target_include_directories(TestApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(TestApplication PUBLIC
        Engine::GeometricTools
        Engine::SphynxApplication
        Engine::Rendering
        Engine::Core
        Engine::Math
        tinyobjloader
        )

target_compile_definitions(TestApplication PRIVATE
        OBJECTS_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/objects/"
        TEXTURES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/"
        SHADERS_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/shaders/"
        )


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE TestApplication)


add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/box.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/box.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/ironpatterndiffuse.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/ironpatterndiffuse.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/ironpatternspecular.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/ironpatternspecular.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/box_specular.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/box_specular.png)


add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/box_whitemask.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/box_whitemask.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/pickaxe.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/pickaxe.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/pickaxenormal.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/pickaxenormal.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/boxnormal.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/boxnormal.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/ironpatternnormal.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/ironpatternnormal.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/pickaxespecular.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/pickaxespecular.png)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/fragment.glsl
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/shaders/fragment.glsl)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/vertex.glsl
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/shaders/vertex.glsl)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/bordervertex.glsl
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/shaders/bordervertex.glsl)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/borderfragment.glsl
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/shaders/borderfragment.glsl)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/objects/untitled.obj
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/objects/untitled.obj)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/objects/untitled.mtl
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/objects/untitled.mtl)