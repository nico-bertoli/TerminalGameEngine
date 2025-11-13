#pragma once
#include <string>
#include <iostream>

#include "General/Singleton.h"
#include "General/Vector2Int.h"

namespace Engine
{
    ////////////////////////////////////////////////////////////////// Color Enum
    enum class TerminalColor
    {
        WHITE_DARK,
        RED_DARK,
        GREEN_DARK,
        BLUE_DARK,
        CYAN_DARK,
        MAGENTA_DARK,
        YELLOW_DARK,
        
        WHITE,
        RED,
        GREEN,
        BLUE,
        CYAN,
        MAGENTA,
        YELLOW,
        GREY,
        BLACK
    };

    ////////////////////////////////////////////////////////////////// BaseTerminal
    class BaseTerminal
    {
    protected:
        TerminalColor currentColor;

    public:
        virtual ~BaseTerminal() = default;
        virtual void Clear() = 0;
        virtual void SetColor(TerminalColor color) = 0;
        virtual TerminalColor GetColor()  = 0;
        virtual void SetCursorPosition(const Vector2Int& position) = 0;
        virtual void SetCursorPosition(int x, int y){SetCursorPosition(Vector2Int(x,y));}
        virtual Vector2Int GetCursorPosition() = 0;

        void Cout(std::string_view s) const;
        void Cout(char c) const;

    protected:
        BaseTerminal() { HideCursor(); }
        virtual void HideCursor() {}
    };
}
