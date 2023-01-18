//
// Created by andre on 27.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_WINDOW_H
#define CHUBBYSPHYNXENGINE_WINDOW_H

// Sphynx Engine
#include <Event.h>

// External
#include <GLFW/glfw3.h>

// STD
#include <string>
#include <functional>

namespace Sphynx {

    class Window {
    private:
        struct WindowData {
            std::string title;
            int width;
            int height;
            bool VSync;
            std::function<void(Event&)> eventCallback;
        };

        WindowData m_data {};
        GLFWwindow * m_window { nullptr };

        void Init() {

        }

        void Shutdown() {}


    public:
        Window();
        ~Window();

        // CHECKS
        bool isVSync() const { return m_data.VSync; }

        // SETTERS
        void setVSync(const bool &enabled) { m_data.VSync = enabled; }

        void setEventCallback(const std::function <void(Event&)> &callback) { m_data.eventCallback = callback; }

        // GETTERS
        std::string getTitle() const {return m_data.title; }

        int getWidth() const {return m_data.width; }

        int getHeight() const { return m_data.height; }

        // BEHAVIOUR

        void onUpdate() {

        }

    };

}

#endif //CHUBBYSPHYNXENGINE_WINDOW_H
