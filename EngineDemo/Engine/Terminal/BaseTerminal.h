#pragma once
#include <string>
#include <iostream>

#include <nbase_kit/singleton.h>
#include "General/Vector2Int.h"

namespace Engine
{
    using TerminalColor = const char*;
    namespace Color
    {
        static constexpr const char* BLACK   = "\033[30m";
        static constexpr const char* RED_DARK = "\033[31m";
        static constexpr const char* GREEN_DARK = "\033[32m";
        static constexpr const char* YELLOW_DARK = "\033[33m";
        static constexpr const char* BLUE_DARK = "\033[34m";
        static constexpr const char* MAGENTA_DARK = "\033[35m";
        static constexpr const char* CYAN_DARK = "\033[36m";
        static constexpr const char* WHITE_DARK = "\033[37m";

        static constexpr const char* GREY   = "\033[90m";
        static constexpr const char* RED    = "\033[91m";
        static constexpr const char* GREEN  = "\033[92m";
        static constexpr const char* YELLOW = "\033[93m";
        static constexpr const char* BLUE   = "\033[94m";
        static constexpr const char* MAGENTA = "\033[38;2;255;0;255m";
        static constexpr const char* CYAN   = "\033[96m";
        static constexpr const char* WHITE  = "\033[97m";

        static constexpr const char* USER_TERMINAL  = "\033[0m";

        // Background colors (standard)
        static constexpr const char* BG_BLACK   = "\033[40m";
        static constexpr const char* BG_RED_DARK = "\033[41m";
        static constexpr const char* BG_GREEN_DARK = "\033[42m";
        static constexpr const char* BG_YELLOW_DARK = "\033[43m";
        static constexpr const char* BG_BLUE_DARK = "\033[44m";
        static constexpr const char* BG_MAGENTA_DARK = "\033[45m";
        static constexpr const char* BG_CYAN_DARK = "\033[46m";
        static constexpr const char* BG_WHITE_DARK = "\033[47m";

        // Background colors (bright)
        static constexpr const char* BG_GREY   = "\033[100m";
        static constexpr const char* BG_RED    = "\033[101m";
        static constexpr const char* BG_GREEN  = "\033[102m";
        static constexpr const char* BG_YELLOW = "\033[103m";
        static constexpr const char* BG_BLUE   = "\033[104m";
        static constexpr const char* BG_MAGENTA = "\033[105m";
        static constexpr const char* BG_CYAN   = "\033[106m";
        static constexpr const char* BG_WHITE  = "\033[107m";
        
        static constexpr const char* BG_USER_TERMINAL = "\033[49m";
    }

    ////////////////////////////////////////////////////////////////// BaseTerminal
    class BaseTerminal
    {
    protected:
        const char* frontColor;
        const char* backColor;

        const char* defaultFrontColor = Color::WHITE;
        const char* defaultBackColor = Color::BG_BLACK;

        //================================================================= ANSI Color Constants

    public:
        virtual ~BaseTerminal(){SetColor(Color::USER_TERMINAL, Color::BG_USER_TERMINAL);}

        const char* GetFrontColor(){ return frontColor; };
        const char* GetBackColor(){ return backColor; };
        void SetColor(const char* frontColor = nullptr, const char* backColor = nullptr);
        void SetDefaultColors(const char* frontColor, const char* backColor);

        virtual void Clear() = 0;
        virtual void SetCursorPosition(const Vector2Int& position) = 0;
        virtual void SetCursorPosition(int x, int y){SetCursorPosition(Vector2Int(x,y));}

        void Cout(std::string_view s) const;
        void Cout(char c) const;
        void Flush() const { std::cout << std::flush; } //grants cout termination before proceeding

    protected:
        BaseTerminal() : frontColor(Color::WHITE), backColor(Color::BG_BLACK), defaultBackColor(Color::BG_BLACK) { HideCursor(); }
        virtual void HideCursor() {}
    };
}
