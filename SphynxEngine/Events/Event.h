//
// Created by andre on 25.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_EVENT_H
#define CHUBBYSPHYNXENGINE_EVENT_H

// Sphynx Engine
#include <SphynxCore.h>

// STD
#include <string>
#include <functional>

namespace Sphynx {

    enum class EventType {
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyRepeat,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        EventCategoryApplication = 1,
        EventCategoryInput       = 2,
        EventCategoryKeyboard    = 4,
        EventCategoryMouse       = 8,
        EventCategoryMouseButton = 16
    };


    class Event {
        friend class EventDispatcher;
    protected:
        bool m_handled {false};

    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual std::string toString() const {return getName();}

        inline bool isInCategory( const EventCategory &category) const {
            return getCategoryFlags() & category;
        }
    };

    class EventDispatcher {
    private:
        Event& m_event;

    public:
        explicit EventDispatcher(Event& event) : m_event(event) {};

        template < typename T, typename F >
        bool Dispatch(const F& func) {
            if(m_event.getEventType() == T::getStaticType()) {
                m_event.m_handled |= func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.toString();
    }


}
#endif //CHUBBYSPHYNXENGINE_EVENT_H
