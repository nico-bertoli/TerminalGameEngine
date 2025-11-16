#pragma once
#include "BaseTerminal.h"
#include "General/Singleton.h"

namespace Engine
{
    class LinuxTerminal : public Singleton<LinuxTerminal>, public BaseTerminal
    {
        friend class Singleton<LinuxTerminal>;

        //================================================================= Fields
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

        static constexpr const char* RESET_COLOR  = "\033[0m";

        static constexpr const char* CLEAR_TERMINAL = "\033[2J\033[3J";


    //================================================================= Override Methods
public:
        void Clear() override;
        void SetColor(TerminalColor color)override;
        TerminalColor GetColor() override { return currentColor; };
        void SetCursorPosition(const Vector2Int& position) override;
        Vector2Int GetCursorPosition() override;

    protected:
        void HideCursor() override {std::cout << "\033[?25l";};

    //================================================================= Methods
public:
    using BaseTerminal::SetCursorPosition;
protected:
    static const char* ToLinuxColor(TerminalColor color);
    };
}