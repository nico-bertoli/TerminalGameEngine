#pragma once
#include <string>
#include <iostream>

#include "General/Singleton.h"
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
        static constexpr const char* MAGENTA = "\033[95m";
        static constexpr const char* CYAN   = "\033[96m";
        static constexpr const char* WHITE  = "\033[97m";
    }

    ////////////////////////////////////////////////////////////////// BaseTerminal
    class BaseTerminal
    {
    protected:
        const char* currentColor;

        //================================================================= ANSI Color Constants

        static constexpr const char* RESET_COLOR  = "\033[0m";

    public:
        virtual ~BaseTerminal() = default;

        const char* GetColor(){ return currentColor; };
        virtual void SetColor(const char* color){std::cout<<color; currentColor = color;}

        virtual void Clear() = 0;
        virtual void SetCursorPosition(const Vector2Int& position) = 0;
        virtual void SetCursorPosition(int x, int y){SetCursorPosition(Vector2Int(x,y));}

        void Cout(std::string_view s) const;
        void Cout(char c) const;
        void Flush() const { std::cout << std::flush; } //grants cout termination before proceeding

    protected:
        BaseTerminal() { HideCursor(); }
        virtual void HideCursor() {}
    };
}
