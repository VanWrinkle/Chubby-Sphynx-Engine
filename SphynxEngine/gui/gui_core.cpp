//
// Created by anmar on 3/28/2024.
//
#include "gui_core.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>
#include <functional>

namespace sphynx {
    void guiCreateContext(GLFWwindow* window, const std::string& glslVersion) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glslVersion.data());
    }

    void guiLoopStart() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void guiRender(GLFWwindow* window) {
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void guiDemo(bool show_another_window) {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    void guiCleanup() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void guiDemoButtonLambdas( const std::function<void()>& onPress ) {
        ImGui::Begin("Function call");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from function call window!");
        ImGui::BeginGroup();
        {
            ImGui::PushItemWidth(5);
            if (ImGui::Button("Call 1"))
                onPress();
            if (ImGui::Button("Call 2"))
                onPress();
            ImGui::PopItemWidth();
        }
        ImGui::EndGroup();
        ImGui::SameLine();
        static bool wireframeRendering = false;
        if (ImGui::Checkbox("Another name", &wireframeRendering)) {
            if(wireframeRendering) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        ImGui::End();
    }
}



