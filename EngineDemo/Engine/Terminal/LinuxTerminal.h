#pragma once
#include "BaseTerminal.h"
#include "General/Singleton.h"
#include <termios.h>

namespace Engine
{
    class LinuxTerminal : public Singleton<LinuxTerminal>, public BaseTerminal
    {
        friend class Singleton<LinuxTerminal>;

        //================================================================= Fields
        static constexpr const char* CLEAR_TERMINAL = "\033[2J\033[3J";

    //================================================================= Constructor/Destructor
    protected:
        LinuxTerminal()  {HideCursor();}
        ~LinuxTerminal() {ShowCursor();}

    //================================================================= Override Methods
    public:
        void Clear() override;
        void SetCursorPosition(const Vector2Int& position) override;

    protected:
        void HideCursor() override;

    //================================================================= Methods
    public:
        using BaseTerminal::SetCursorPosition;
        void ShowCursor();
    };
}