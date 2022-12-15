//
// Created by anmar on 9/18/2022.
//

#ifndef LAB1_LAB2APPLICATION_H
#define LAB1_LAB2APPLICATION_H

#include <GLFWApplication.h>

class Lab4Application : public glfwApp::GLFWApplication {
private:

public:
    Lab4Application(const std::string& name, const std::string& version);
    int run() override;

};

#endif //LAB1_LAB2APPLICATION_H
