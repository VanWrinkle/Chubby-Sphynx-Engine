
add_library( Rendering
        camera/freecamera.h
        SphynxRendering.h
        buffers/indexbuffer.cpp
        modelsystem/modelmatrix.h
        gl_control/rendercommands.h
        shader/shader.cpp
        shader/shadersdatatype.h
        buffers/vertexarray.cpp
        buffers/vertexbuffer.cpp
        texturemanager/texturemanager.cpp
        lighting/lights.h
        camera/camera.h
        camera/perspectivecamera.h
        modelsystem/model.cpp
        )

target_include_directories(Rendering PUBLIC .)

add_library(Engine::Rendering ALIAS Rendering)


target_compile_definitions(Rendering PRIVATE
        STB_IMAGE_IMPLEMENTATION
        STB_IMAGE_STATIC
        TINYOBJLOADER_IMPLEMENTATION
        )

target_link_libraries(Rendering PUBLIC glm glad glfw stb tinyobjloader)



