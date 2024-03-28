//
// Created by anmar on 3/28/2024.
//

#ifndef CHUBBYSPHYNXENGINE_GUI_CORE_H
#define CHUBBYSPHYNXENGINE_GUI_CORE_H

#include <string>
#include <GLFW/glfw3.h>

namespace sphynx {
    void guiCreateContext(GLFWwindow* window, const std::string& glslVersion);

    void guiLoopStart();

    void guiRender();

    void guiDemo(bool show_another_window);

    void guiCleanup();
}

#endif //CHUBBYSPHYNXENGINE_GUI_CORE_H
