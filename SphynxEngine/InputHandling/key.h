//
// Created by anmar on 10/5/2022.
//

#ifndef PROG2002_KEY_H
#define PROG2002_KEY_H

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <iostream>

namespace Input {

    enum class KeyMode {
        CONTINUOUS,
        DISCRETE,
        COOLDOWN
    };

    enum class Key {
        LEFT = GLFW_KEY_LEFT,
        RIGHT = GLFW_KEY_RIGHT,
        UP = GLFW_KEY_UP,
        DOWN = GLFW_KEY_DOWN,
        Q = GLFW_KEY_Q,
        W = GLFW_KEY_W,
        E = GLFW_KEY_E,
        R = GLFW_KEY_R,
        T = GLFW_KEY_T,
        Y = GLFW_KEY_Y,
        U = GLFW_KEY_U,
        I = GLFW_KEY_I,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K ,
        L = GLFW_KEY_L,
        Z = GLFW_KEY_Z,
        X = GLFW_KEY_X,
        C = GLFW_KEY_C,
        V = GLFW_KEY_V,
        B = GLFW_KEY_B,
        N = GLFW_KEY_N,
        M = GLFW_KEY_M,
        ENTER = GLFW_KEY_ENTER,
        ESCAPE = GLFW_KEY_ESCAPE,
        SPACE = GLFW_KEY_SPACE,
        L_SHIFT = GLFW_KEY_LEFT_SHIFT
    };

    class Keyboard {
    private:
        struct KeyLogic {
            float cooldown        {};
            float cooldownCounter {};
            int currentState      {};
            int previousState     {GLFW_RELEASE};
            KeyMode mode          {};
            bool pressed = false;
        };

        static inline std::unordered_map<int, KeyLogic> m_keybinds {};

    public:
        explicit Keyboard() = default;

        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto it = m_keybinds.find(key);
            if(it != m_keybinds.end()) {
                it->second.previousState = it->second.currentState;
                it->second.currentState = action;
            } else {
                setKeyBehaviour(static_cast<Key>(key));
                it = m_keybinds.find(key);
                if(it != m_keybinds.end()) {
                    it->second.currentState = action;
                }
            }
        }


        static void setKeyBehaviour(Key keyID, KeyMode mode = KeyMode::DISCRETE, float cooldown = 0) {
            auto it = m_keybinds.find(static_cast<int>(keyID));
            if(it == m_keybinds.end()) {
                KeyLogic newKey;
                newKey.mode = mode;
                newKey.cooldown = cooldown;

                m_keybinds.insert({static_cast<int>(keyID), newKey});
            } else {
                it->second.currentState = GLFW_RELEASE;
                it->second.previousState = GLFW_RELEASE;
                it->second.cooldown = cooldown;
                it->second.mode = mode;
                it->second.cooldownCounter = 0.0f;
            }
        };


        static void updateTimers(const float &deltaTime) {
            for(auto keybind : m_keybinds) {
                if(keybind.second.cooldown != 0.0f) {
                    keybind.second.cooldownCounter -= deltaTime;
                }
            }
        }


        static bool isKeyActive(Key keyID) {
            auto it = m_keybinds.find(static_cast<int>(keyID));
            if(it != m_keybinds.end()) {
                switch(it->second.mode) {
                    case KeyMode::DISCRETE: {
                        bool temp = it->second.currentState == GLFW_PRESS && !it->second.pressed;
                        it->second.pressed = (it->second.currentState == GLFW_PRESS);
                        return (temp);
                    }
                    case KeyMode::CONTINUOUS: {
                        return (it->second.currentState == GLFW_PRESS ||
                                it->second.currentState == GLFW_REPEAT);
                    }
                    case KeyMode::COOLDOWN : {
                        if(0 < it->second.cooldownCounter) {
                            return false;
                        } else {
                            return (it->second.currentState == GLFW_PRESS &&
                                    it->second.previousState != GLFW_PRESS &&
                                    it->second.previousState != GLFW_REPEAT);
                        }
                    }
                }
            }
            return false;
        }


    };
}

#endif //PROG2002_KEY_H
