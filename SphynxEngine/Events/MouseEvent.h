//
// Created by andre on 27.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_MOUSEEVENT_H
#define CHUBBYSPHYNXENGINE_MOUSEEVENT_H

#include <Event.h>
#include <sstream>

namespace Sphynx {


    class MouseButtonPressedEvent : public Event {
    private:
        MouseCode m_mouseCode;
    public:
        explicit MouseButtonPressedEvent(const MouseCode &code) : m_mouseCode(code) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressed: " << static_cast<int>(m_mouseCode);
            return ss.str();
        }


        MouseCode getMouseCode() { return m_mouseCode; }
        int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton; }
        static EventType getStaticType() { return EventType::MouseButtonPressed; }
        EventType getEventType() const override { return getStaticType(); }
        const char * getName() const override { return "MouseButtonPressed"; }
    };


    class MouseButtonReleasedEvent : public Event {
    private:
        MouseCode m_mouseCode;
    public:
        explicit MouseButtonReleasedEvent(const MouseCode &code) : m_mouseCode(code) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleased: " << static_cast<int>(m_mouseCode);
            return ss.str();
        }
        MouseCode getMouseCode() { return m_mouseCode; }
        int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton; }
        static EventType getStaticType() { return EventType::MouseButtonReleased; }
        EventType getEventType() const override { return getStaticType(); }
        const char * getName() const override { return "MouseButtonReleased"; }
    };


    class MouseMovedEvent : public Event {
    private:
        float m_xDelta;
        float m_yDelta;

    public:
        explicit MouseMovedEvent(const float &xDelta, const float &yDelta) :
                                                            m_xDelta(xDelta), m_yDelta(yDelta) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: x: " << m_xDelta << " y: " << m_yDelta;
            return ss.str();
        }

        float getX() { return m_xDelta; }
        float getY() { return m_yDelta; }
        int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        static EventType getStaticType() { return EventType::MouseMoved; }
        EventType getEventType() const override { return getStaticType(); }
        const char * getName() const override { return "MouseButtonPressed"; }
    };


    class MouseScrolled : public Event {
    private:
        float m_xDelta;
        float m_yDelta;

    public:
        explicit MouseScrolled(const float &xDelta, const float &yDelta) :
                m_xDelta(xDelta), m_yDelta(yDelta) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: x: " << m_xDelta << " y: " << m_yDelta;
            return ss.str();
        }

        float getX() { return m_xDelta; }
        float getY() { return m_yDelta; }
        int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        static EventType getStaticType() { return EventType::MouseScrolled; }
        EventType getEventType() const override { return getStaticType(); }
        const char * getName() const override { return "MouseScrolled"; }
    };

}


#endif //CHUBBYSPHYNXENGINE_MOUSEEVENT_H
