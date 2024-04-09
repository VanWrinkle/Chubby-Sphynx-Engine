//
// Created by anmar on 10/5/2022.
//

#ifndef PROG2002_MOUSE_H
#define PROG2002_MOUSE_H

// External
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "./MouseCodes.h"
#include <tuple>

static const Sphynx::MouseCode buttonCodes[] = {
    Sphynx::MouseCode::ButtonLeft,
    Sphynx::MouseCode::ButtonRight,
    Sphynx::MouseCode::ButtonMiddle,
    Sphynx::MouseCode::Button3,
    Sphynx::MouseCode::Button4,
    Sphynx::MouseCode::Button5,
    Sphynx::MouseCode::Button6,
    Sphynx::MouseCode::Button7,
    };

namespace Sphynx {

    class Mouse {

        enum class MouseButtonState {
            JustPressed,
            Pressed,
            JustReleased,
            Released
        };


    private:
        inline static Mouse* m_instance = nullptr;
        inline static double m_prevX {};
        inline static double m_prevY {};
        inline static double m_posX {};
        inline static double m_posY {};
        inline static double m_scroll {};
        GLFWwindow* m_window = nullptr;
        inline static std::vector<MouseButtonState> m_buttonStates {};




        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
            if(m_buttonStates.empty()) {
                for(auto _ : buttonCodes) {
                    m_buttonStates.push_back(MouseButtonState::Released);
                }
            }
            try {
                const auto currentMouseState = m_buttonStates.at(button);
                if(action == GLFW_PRESS) {
                    if(currentMouseState == MouseButtonState::Released || currentMouseState == MouseButtonState::JustReleased) {
                        m_buttonStates[button] = MouseButtonState::JustPressed;
                    } else {
                        m_buttonStates[button] = MouseButtonState::Pressed;
                    }
                } else {
                    if(currentMouseState == MouseButtonState::Pressed || currentMouseState == MouseButtonState::JustPressed) {
                        m_buttonStates[button] = MouseButtonState::JustReleased;
                    } else {
                        m_buttonStates[button] = MouseButtonState::Released;
                    }
                }
            }
            catch (...) {

            }

        }

        static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
            m_posX = xpos;
            m_posY = ypos;
        }

        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
            m_scroll += yoffset;
        }

    public:
        explicit Mouse() {
            for(auto _ : buttonCodes) {
                m_buttonStates.push_back(MouseButtonState::Released);
            }
        }

        void registerCallbacks(GLFWwindow* window) {
            m_window = window;
            glfwSetScrollCallback(window, Mouse::scrollCallback);
            glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
            glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
        }

        static Mouse* getInstance() {
            if(m_instance == nullptr) {
                m_instance = new Mouse();
            }
            return m_instance;
        }



        static void update(const float dt = 0.0f) {
//
            m_prevY = m_posY;
            m_prevX = m_posX;
//            m_posX = 0;
//            m_posY = 0;
            m_scroll = 0;
//            glfwGetCursorPos(m_window, &m_posX, &m_posY);
//
//            if( m_smoothing ) {
//                float factor = std::max( m_factor*dt, m_minStep);
//                m_posX = m_prevX * (1.0 - factor) + m_posX * factor;
//                m_posY = m_prevY * (1.0 - factor) + m_posY * factor;
//            }

//            for(auto code : buttonCodes) {
//                const int glfwState = glfwGetMouseButton(m_window, (int)code);
//                const auto currentMouseState = m_buttonStates[(int)code];
//                if(glfwState == GLFW_PRESS) {
//                    if(currentMouseState == MouseButtonState::Released || currentMouseState == MouseButtonState::JustReleased) {
//                        m_buttonStates[(int)code] = MouseButtonState::JustPressed;
//                    } else {
//                        m_buttonStates[(int)code] = MouseButtonState::Pressed;
//                    }
//                } else {
//                    if(currentMouseState == MouseButtonState::Pressed || currentMouseState == MouseButtonState::JustPressed) {
//                        m_buttonStates[(int)code] = MouseButtonState::JustReleased;
//                    } else {
//                        m_buttonStates[(int)code] = MouseButtonState::Released;
//                    }
//                }
//            }
        }

        static bool isButtonDown(Sphynx::MouseButton button) {
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::Pressed || state == MouseButtonState::JustPressed;
            }
            catch (...) {
                return false;
            }
        }

        static bool isButtonUp(Sphynx::MouseButton button) {
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::Released || state == MouseButtonState::JustReleased;
            }
            catch (...) {
                return false;
            }
        }

        static bool isButtonPressed(Sphynx::MouseButton button){
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::JustPressed;
            }
            catch (...) {
                return false;
            }
        }

        static bool isButtonReleased(Sphynx::MouseButton button){
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::JustReleased;
            }
            catch (...) {
                return false;
            }
        }

        [[nodiscard]] static glm::vec2 getMouseDelta() {
            return {m_posX - m_prevX, m_posY - m_prevY};
        }

        void captureMouse() {
            if(m_window == nullptr) return;
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        static glm::vec2 getCursorPosition() {
            return {m_posX, m_posY};
        }

        static double getScroll() {
            return m_scroll;
        }

        void releaseMouse() {
            if(m_window == nullptr) return;
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    };
}

#endif //PROG2002_MOUSE_H

