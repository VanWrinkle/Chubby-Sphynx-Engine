//
// Created by andre on 14.09.22.
//

#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "tclap/CmdLine.h"

namespace glfwApp {

    class GLFWApplication {
    public:
        GLFWApplication(std::string  name, std::string  version);
        ~GLFWApplication();



        virtual unsigned parseArguments(const int &argc, char **argv);

        virtual unsigned initialize();

        virtual int run() = 0;

    protected:
        std::string m_name;
        std::string m_version;
        GLFWwindow *m_window  {nullptr};
        int m_width  {};
        int m_height {};
    };














}

#endif //_GLFWAPPLICATION_H
