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
    Sphynx::MouseCode::Button0,
    Sphynx::MouseCode::Button1,
    Sphynx::MouseCode::Button3,
    Sphynx::MouseCode::Button4,
    Sphynx::MouseCode::Button5,
    Sphynx::MouseCode::Button6,
    Sphynx::MouseCode::Button7,
    Sphynx::MouseCode::ButtonLeft,
    Sphynx::MouseCode::ButtonRight,
    Sphynx::MouseCode::ButtonMiddle
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
        double m_prevX {};
        double m_prevY {};
        double m_posX  {};
        double m_posY  {};
        GLFWwindow *m_window;
        bool  m_smoothing {false};
        float m_factor {};
        float m_minStep{};
        std::vector<MouseButtonState> m_buttonStates {};



    public:
        explicit Mouse(GLFWwindow* window) : m_window(window){
            for(auto code : buttonCodes) {
                m_buttonStates.push_back(MouseButtonState::Released);
            }
        }

        void update(const float dt = 0.0f) {
            m_prevX = m_posX;
            m_prevY = m_posY;
            glfwGetCursorPos(m_window, &m_posX, &m_posY);

            if( m_smoothing ) {
                float factor = std::max( m_factor*dt, m_minStep);
                m_posX = m_prevX * (1.0 - factor) + m_posX * factor;
                m_posY = m_prevY * (1.0 - factor) + m_posY * factor;
            }

            for(auto code : buttonCodes) {
                const int glfwState = glfwGetMouseButton(m_window, (int)code);
                const auto currentMouseState = m_buttonStates[(int)code];
                if(glfwState == GLFW_PRESS) {
                    if(currentMouseState == MouseButtonState::Released || currentMouseState == MouseButtonState::JustReleased) {
                        m_buttonStates[(int)code] = MouseButtonState::JustPressed;
                    } else {
                        m_buttonStates[(int)code] = MouseButtonState::Pressed;
                    }
                } else {
                    if(currentMouseState == MouseButtonState::Pressed || currentMouseState == MouseButtonState::JustPressed) {
                        m_buttonStates[(int)code] = MouseButtonState::JustReleased;
                    } else {
                        m_buttonStates[(int)code] = MouseButtonState::Released;
                    }
                }
            }
        }

        bool isButtonDown(Sphynx::MouseButton button) {
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::Pressed || state == MouseButtonState::JustPressed;
            }
            catch (...) {
                return false;
            }
        }

        bool isButtonUp(Sphynx::MouseButton button) {
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::Released || state == MouseButtonState::JustReleased;
            }
            catch (...) {
                return false;
            }
        }

        bool isButtonPressed(Sphynx::MouseButton button){
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::JustPressed;
            }
            catch (...) {
                return false;
            }
        }

        bool isButtonReleased(Sphynx::MouseButton button){
            try {
                const auto state =  m_buttonStates.at((int)button);
                return state == MouseButtonState::JustReleased;
            }
            catch (...) {
                return false;
            }
        }

        void resetDelta() {
            glfwGetCursorPos(m_window, &m_posX, &m_posY);
            m_prevX = m_posX;
            m_prevY = m_posY;
        }

        void enableSmoothing(float factor = 1.0f, const float &minStep = 0.0f) {
            m_factor = factor;// std::min(std::max(factor, 0.0f), 1.0f);
            m_smoothing = true;
        }

        void disableSmoothing() {
            m_smoothing = false;
        }

        void setSmoothing(const float &factor) {
            m_factor = std::min(std::max(factor, 0.0f), 1.0f);
        }

        [[nodiscard]] glm::vec2 getMouseDelta() const {
            return {m_posX - m_prevX, m_posY - m_prevY};
        }

        void captureMouse() {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        void releaseMouse() {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    };
}

#endif //PROG2002_MOUSE_H

