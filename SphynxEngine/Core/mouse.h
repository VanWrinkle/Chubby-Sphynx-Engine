//
// Created by anmar on 10/5/2022.
//

#ifndef PROG2002_MOUSE_H
#define PROG2002_MOUSE_H

// External
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Sphynx {

    class Mouse {
    private:
        double m_prevX {};
        double m_prevY {};
        double m_posX  {};
        double m_posY  {};
        GLFWwindow *m_window;
        bool  m_smoothing {false};
        float m_factor {};
        float m_minStep{};

    public:
        explicit Mouse(GLFWwindow* window) : m_window(window){}

        void update(const float dt = 0.0f) {
            m_prevX = m_posX;
            m_prevY = m_posY;
            glfwGetCursorPos(m_window, &m_posX, &m_posY);

            if( m_smoothing ) {
                float factor = std::max( m_factor*dt, m_minStep);
                m_posX = m_prevX * (1.0 - factor) + m_posX * factor;
                m_posY = m_prevY * (1.0 - factor) + m_posY * factor;
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

