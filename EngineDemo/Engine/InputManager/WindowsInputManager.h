#pragma once
#include <windows.h>
#include <unordered_map>
#include <nbase_kit/singleton.h>
#include "BaseInputManager.h"

namespace Engine
{

class WindowsInputManager : public nbase_kit::Singleton<WindowsInputManager>, public BaseInputManager
{
private:
    inline static const  std::unordered_map<Key, int> keyMap =
    {
        {Key::SPACE, VK_SPACE},
        {Key::W, 0x57},
        {Key::A, 0x41},
        {Key::S, 0x53},
        {Key::D, 0x44},
        {Key::ARROW_UP, VK_UP},
        {Key::ARROW_DOWN, VK_DOWN},
        {Key::ARROW_LEFT, VK_LEFT},
        {Key::ARROW_RIGHT, VK_RIGHT},
        {Key::NUM_0, 0x30},
        {Key::NUM_1, 0x31},
        {Key::NUM_2, 0x32},
        {Key::NUM_3, 0x33},
        {Key::NUM_4, 0x34},
        {Key::NUM_5, 0x35},
        {Key::NUM_6, 0x36},
        {Key::NUM_7, 0x37},
        {Key::NUM_8, 0x38},
        {Key::NUM_9, 0x39},
        {Key::ESC, VK_ESCAPE}
    };
    
public:
    inline bool IsKeyPressed(Key key)
    {
        if (keyMap.find(key) != keyMap.end())
            return GetAsyncKeyState(keyMap.at(key)) & 0x8000;

        return false;
    }

    inline bool IsAnyKeyPressed()
    {
        for (int i = 0; i < 256; ++i)
            if (GetAsyncKeyState(i) & 0x8000)
                return true;

        return false;
    }
};

} // namespace Engine