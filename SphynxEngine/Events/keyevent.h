//
// Created by andre on 25.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_KEYEVENT_H
#define CHUBBYSPHYNXENGINE_KEYEVENT_H

// Sphynx Engine
#include "event.h"


// STD

class KeyEvent {
private:
    int m_keyCode;
public:
    KeyEvent(const int & code) {

    }
};

class KeyPressEvent : public KeyEvent {

};

class KeyReleaseEvent : public KeyEvent {

};

class KeyRepeatEvent : public KeyEvent  {

};



#endif //CHUBBYSPHYNXENGINE_KEYEVENT_H
