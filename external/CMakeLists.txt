add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(tclap)
add_subdirectory(tinyobjloader)
add_subdirectory(glad)
add_subdirectory(spdlog)
# -------------- IMGUI static library creation`
#
set(IMGUI_PATH ./imgui)
file(GLOB IMGUI_GLOB
        ${IMGUI_PATH}/imgui.h
        ${IMGUI_PATH}/imgui.cpp
        ${IMGUI_PATH}/imconfig.h
        ${IMGUI_PATH}/imgui_demo.cpp
        ${IMGUI_PATH}/imgui_draw.cpp
        ${IMGUI_PATH}/imgui_internal.h
        ${IMGUI_PATH}/imstb_rectpack.h
        ${IMGUI_PATH}/imstb_textedit.h
        ${IMGUI_PATH}/imstb_truetype.h
        ${IMGUI_PATH}/imgui_tables.cpp
        ${IMGUI_PATH}/imgui_widgets.cpp

        # specific bindings...
        ${IMGUI_PATH}/backends/imgui_impl_glfw.h
        ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.h)
add_library(ImGui STATIC ${IMGUI_GLOB})
target_include_directories(ImGui PUBLIC ${IMGUI_PATH})
target_link_libraries(ImGui PRIVATE glfw)
# ----------------------------------------------------------------------

add_library(stb INTERFACE ./stb/stb_image.h)
target_include_directories(stb INTERFACE ./stb)