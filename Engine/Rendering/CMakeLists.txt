
add_library( Rendering
        freecamera.h
        rendering.h
        indexbuffer.cpp
        modelmatrix.h
        rendercommands.h
        shader.cpp
        shadersdatatype.h
        vertexarray.cpp
        vertexbuffer.cpp
        texturemanager.cpp
        lights.h
        camera.h
        perspectivecamera.h
        model.cpp
        )
target_include_directories(Rendering PUBLIC .)

add_library(Engine::Rendering ALIAS Rendering)


target_compile_definitions(Rendering PRIVATE
        STB_IMAGE_IMPLEMENTATION
        STB_IMAGE_STATIC
        TINYOBJLOADER_IMPLEMENTATION
        )

target_link_libraries(Rendering PUBLIC glm glad glfw stb tinyobjloader)



