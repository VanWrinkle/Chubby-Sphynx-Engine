//
// Created by anmar on 10/5/2022.
//

#ifndef PROG2002_KEY_H
#define PROG2002_KEY_H


// External
#include <GLFW/glfw3.h>

// STD
#include <unordered_map>
#include <iostream>

namespace SphynxIO {

    enum class KeyMode {
        CONTINUOUS,
        DISCRETE,
        COOLDOWN
    };

    enum class KeyCode { // Uses GLFW Keycodes for now
        Space = GLFW_KEY_SPACE,
        Apostrophe = GLFW_KEY_APOSTROPHE,  /* ' */
        Comma = GLFW_KEY_COMMA,  /* , */
        Minus = GLFW_KEY_MINUS, /* - */
        Period = GLFW_KEY_PERIOD,  /* . */
        Slash = GLFW_KEY_SLASH,  /* / */

        D0 = GLFW_KEY_0,
        D1 = GLFW_KEY_1,
        D2 = GLFW_KEY_2,
        D3 = GLFW_KEY_3,
        D4 = GLFW_KEY_4,
        D5 = GLFW_KEY_5,
        D6 = GLFW_KEY_6,
        D7 = GLFW_KEY_7,
        D8 = GLFW_KEY_8,
        D9 = GLFW_KEY_9,

        Semicolon = GLFW_KEY_SEMICOLON,  /* ; */
        Equal = GLFW_KEY_EQUAL,  /* = */

        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,

        LeftBracket = GLFW_KEY_LEFT_BRACKET,  /* [ */
        Backslash = GLFW_KEY_BACKSLASH,  /* \ */
        rightBracket = GLFW_KEY_RIGHT_BRACKET,  /* ] */
        GraveAccent = GLFW_KEY_GRAVE_ACCENT,  /* ` */

        World1 = GLFW_KEY_WORLD_1, /* non-US #1 */
        World2 = GLFW_KEY_WORLD_2, /* non-US #2 */

        Escape = GLFW_KEY_ESCAPE,
        Enter = GLFW_KEY_ENTER,
        Tab = GLFW_KEY_TAB,
        Backspace = GLFW_KEY_BACKSPACE,
        Insert = GLFW_KEY_INSERT,
        Delete = GLFW_KEY_DELETE,

        Right = GLFW_KEY_RIGHT,
        Left = GLFW_KEY_LEFT,
        Down = GLFW_KEY_DOWN,
        Up = GLFW_KEY_UP,

        PageUp = GLFW_KEY_PAGE_UP,
        PageDown = GLFW_KEY_PAGE_DOWN,
        Home = GLFW_KEY_HOME,
        End = GLFW_KEY_END,
        CapsLock = GLFW_KEY_CAPS_LOCK,
        ScrollLock = GLFW_KEY_SCROLL_LOCK,
        NumLock = GLFW_KEY_NUM_LOCK,
        PrintScreen = GLFW_KEY_PRINT_SCREEN,
        Pause = GLFW_KEY_PAUSE,

        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,

        Keypad0 = GLFW_KEY_KP_0,
        Keypad1 = GLFW_KEY_KP_1,
        Keypad2 = GLFW_KEY_KP_2,
        Keypad3 = GLFW_KEY_KP_3,
        Keypad4 = GLFW_KEY_KP_4,
        Keypad5 = GLFW_KEY_KP_5,
        Keypad6 = GLFW_KEY_KP_6,
        Keypad7 = GLFW_KEY_KP_7,
        Keypad8 = GLFW_KEY_KP_8,
        Keypad9 = GLFW_KEY_KP_9,
        KeypadDecimal = GLFW_KEY_KP_DECIMAL,
        KeypadDivide = GLFW_KEY_KP_DIVIDE,
        KeypadMultiply = GLFW_KEY_KP_MULTIPLY,
        KeypadSubtract = GLFW_KEY_KP_SUBTRACT,
        KeypadAdd = GLFW_KEY_KP_ADD,
        KeypadEnter = GLFW_KEY_KP_ENTER,
        KeypadEqual = GLFW_KEY_KP_EQUAL,

        LeftShift = GLFW_KEY_LEFT_SHIFT,
        LeftCtrl = GLFW_KEY_LEFT_CONTROL,
        LeftAlt = GLFW_KEY_LEFT_ALT,
        LeftSuper = GLFW_KEY_LEFT_SUPER,
        RightShift = GLFW_KEY_RIGHT_SHIFT,
        RightCtrl = GLFW_KEY_RIGHT_CONTROL,
        RightAlt = GLFW_KEY_RIGHT_ALT,
        RightSuper = GLFW_KEY_RIGHT_SUPER,

        Menu = GLFW_KEY_MENU,
        Last = GLFW_KEY_MENU
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
                setKeyBehaviour(static_cast<KeyCode>(key));
                it = m_keybinds.find(key);
                if(it != m_keybinds.end()) {
                    it->second.currentState = action;
                }
            }
        }


        static void setKeyBehaviour(KeyCode keyID, KeyMode mode = KeyMode::DISCRETE, float cooldown = 0) {
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


        static bool isKeyActive(KeyCode keyID) {
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
