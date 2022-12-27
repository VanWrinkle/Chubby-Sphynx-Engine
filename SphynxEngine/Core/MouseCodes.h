//
// Created by andre on 26.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_MOUSECODES_H
#define CHUBBYSPHYNXENGINE_MOUSECODES_H

namespace Sphynx {
    enum class MouseCode {
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    } typedef MouseButton; ///< Alias of MouseCode
}

#endif //CHUBBYSPHYNXENGINE_MOUSECODES_H
