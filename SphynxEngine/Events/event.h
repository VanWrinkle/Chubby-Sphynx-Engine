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

#define BIT(x) (1 << x)

namespace Sphynx {

    enum class EventType {
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyRepeat,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        EventCategoryApplication = BIT(0),
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3),
        EventCategoryMouseButton = BIT(4)
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
            if(m_event.getEventType() == T::GetStaticType()) {
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
