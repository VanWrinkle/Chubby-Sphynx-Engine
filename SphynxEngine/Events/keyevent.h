//
// Created by andre on 25.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_KEYEVENT_H
#define CHUBBYSPHYNXENGINE_KEYEVENT_H

// Sphynx Engine
#include "event.h"
#include <SphynxCore.h>

// STD
#include <string>
#include <sstream>


namespace Sphynx {

    /**
     * Abstract cass basis for KeyPressEvent, KeyReleaseEvent and KeyRepeatEvent
     */
    class KeyEvent : public Event{
    protected:
        Sphynx::KeyCode m_keyCode;
        KeyEvent(const KeyCode & keyCode) : m_keyCode(keyCode) {}

    public:
        KeyCode getKeyCode() { return m_keyCode; }
        int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

    };


    class KeyPressEvent : public KeyEvent {
    public:
        KeyPressEvent( const KeyCode &keyCode ) : KeyEvent(keyCode) {}
        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressEvent: " << static_cast<int>(m_keyCode);
            return ss.str();
        }
        static EventType getStaticType() { return EventType::KeyPressed; }
    };


    class KeyReleaseEvent : public KeyEvent {
    public:
        KeyReleaseEvent( const KeyCode &keyCode ) : KeyEvent( keyCode ) {}
        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressEvent: " << static_cast<int>(m_keyCode);
            return ss.str();
        }
        static EventType getStaticType() { return EventType::KeyReleased; }
    };


    class KeyRepeatEvent : public KeyEvent  {
    public:
        KeyRepeatEvent( const KeyCode &keyCode ) : KeyEvent( keyCode ) {}
        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyRepeatEvent: " << static_cast<int>(m_keyCode);
            return ss.str();
        }
        static EventType getStaticType() { return EventType::KeyRepeat; }
    };
}



#endif //CHUBBYSPHYNXENGINE_KEYEVENT_H
