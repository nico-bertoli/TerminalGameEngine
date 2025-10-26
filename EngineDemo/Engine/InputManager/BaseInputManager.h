#pragma once
#include <unordered_map>

namespace Engine
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

    class BaseInputManager 
    {
public:
        virtual bool IsKeyPressed(Key key) = 0;
        virtual bool IsAnyKeyPressed() = 0;
    };

}

//allows using Key in hash maps
namespace std
{
    template <>
    struct hash<Engine::Key>
    {
        size_t operator()(const Engine::Key& k) const noexcept
        {
            return std::hash<int>()(static_cast<int>(k));
        }
    };
}