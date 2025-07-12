#pragma once
#include <Windows.h>
#include <unordered_map>

namespace Engine
{
    namespace InputUtils
    {
        enum class Key
        {
            SPACE,
            W,
            A,
            S,
            D,

            ARROW_UP,
            ARROW_DOWN,
            ARROW_LEFT,
            ARROW_RIGHT,

            NUM_0,
            NUM_1,
            NUM_2,
            NUM_3,
            NUM_4,
            NUM_5,
            NUM_6,
            NUM_7,
            NUM_8,
            NUM_9,

            ESC,
        };

        static std::unordered_map<Key, int> keyMap =
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

        inline bool IsKeyPressed(Key key)
        {
            if (keyMap.find(key) != keyMap.end())
            {
                return GetAsyncKeyState(keyMap[key]) & 0x8000;
            }
            return false;
        }

        inline bool IsAnyKeyPressed()
        {
            for (int i = 0; i < 256; ++i)
                if (GetAsyncKeyState(i) & 0x8000)
                    return true;

            return false;
        }
    }
}