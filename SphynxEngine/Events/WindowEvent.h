//
// Created by andre on 27.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_WINDOWEVENT_H
#define CHUBBYSPHYNXENGINE_WINDOWEVENT_H

#include <Event.h>
#include <sstream>



namespace Sphynx {

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;
        int getCategoryFlags() const override { return EventCategoryApplication; }
        static EventType getStaticType() { return EventType::WindowClose; }
        EventType getEventType() const override { return getStaticType(); }
        const char * getName() const override { return "WindowCloseEvent"; }
    };


    class WindowResizeEvent : public Event {
    private:
        int m_width;
        int m_height;

    public:
        WindowResizeEvent(const int &width, const int &height) : m_width(width), m_height(height) {}
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_width << ", " << m_height;
            return ss.str();
        }
        int getCategoryFlags() const override { return EventCategoryApplication; }
        static EventType getStaticType() { return EventType::WindowResize; }
        EventType getEventType() const override { return getStaticType(); }
        const char * getName() const override { return "windowResizeEvent"; }
    };

}

#endif //CHUBBYSPHYNXENGINE_WINDOWEVENT_H
