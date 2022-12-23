//
// Created by andre on 14.09.22.
//
#ifndef SPHYNX_APPLICATION_H
#define SPHYNX_APPLICATION_H

// External
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tclap/CmdLine.h>


// STD
#include <string>

namespace Sphynx {

    class Application {
    public:
        Application(std::string  name, std::string  version);
        ~Application();

        virtual int parseArguments(const int &argc, char **argv);

        virtual int initialize();

        virtual int run() = 0;

    protected:
        std::string m_name;
        std::string m_version;
        GLFWwindow *m_window  {nullptr};
        int m_width  {};
        int m_height {};
    };
}

#endif //SPHYNX_APPLICATION_H
