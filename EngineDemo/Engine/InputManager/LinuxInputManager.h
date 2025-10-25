#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>

#ifdef Status
#undef Status   //removing cause collides with sfml Status define
#endif

#include <unordered_map>

#include "General/Singleton.h"
#include "BaseInputManager.h"

namespace Engine
{

class LinuxInputManager : public Singleton<LinuxInputManager>, public BaseInputManager
{
private:
    inline static const std::unordered_map<Key, KeySym> keyMap =
    {
        {Key::SPACE,      XK_space},
        {Key::W,          XK_w},
        {Key::A,          XK_a},
        {Key::S,          XK_s},
        {Key::D,          XK_d},
        {Key::ARROW_UP,   XK_Up},
        {Key::ARROW_DOWN, XK_Down},
        {Key::ARROW_LEFT, XK_Left},
        {Key::ARROW_RIGHT,XK_Right},
        {Key::NUM_0,      XK_0},
        {Key::NUM_1,      XK_1},
        {Key::NUM_2,      XK_2},
        {Key::NUM_3,      XK_3},
        {Key::NUM_4,      XK_4},
        {Key::NUM_5,      XK_5},
        {Key::NUM_6,      XK_6},
        {Key::NUM_7,      XK_7},
        {Key::NUM_8,      XK_8},
        {Key::NUM_9,      XK_9},
        {Key::ESC,        XK_Escape}
    };

    Display* display = nullptr;

public:
    LinuxInputManager()
    {
        XInitThreads();
        display = XOpenDisplay(nullptr);
    }

    ~LinuxInputManager()
    {
        if (display != nullptr)
        {
            XCloseDisplay(display);
            display = nullptr;
        }
    }

    inline bool IsKeyPressed(Key key) override
    {
        if (display == nullptr)
            return false;

        auto mapping = keyMap.find(key);
        if (mapping == keyMap.end())
            return false;

        const KeyCode keyCode = XKeysymToKeycode(display, mapping->second);
        if (keyCode == 0)
            return false;

        char keys[32] = {0};
        XLockDisplay(display);
        XQueryKeymap(display, keys);
        XUnlockDisplay(display);

        const int byteIndex = keyCode / 8;
        const int bitIndex = keyCode % 8;
        return (keys[byteIndex] & (1 << bitIndex)) != 0;
    }

    inline bool IsAnyKeyPressed() override
    {
        if (display == nullptr)
            return false;

        char keys[32] = {0};
        XLockDisplay(display);
        XQueryKeymap(display, keys);
        XUnlockDisplay(display);

        for (const char keyState : keys)
        {
            if (keyState != 0)
                return true;
        }

        return false;
    }
};

} // namespace Engine
