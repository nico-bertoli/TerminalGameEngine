#pragma once
#include <terme/terminal/base_terminal.h>
#include <nbase_kit/singleton.h>
#include <nbase_kit/matrix.h>

namespace terme
{
    class WindowsTerminal : public nbase_kit::Singleton<WindowsTerminal>, public BaseTerminal
    {
        friend class nbase_kit::Singleton<WindowsTerminal>;

    //================================================================= Override Methods
    public:
        void Clear() override;
        void SetCursorPosition(const vector2_int& position) override;

    protected:
        void HideCursor() override;

    //================================================================= Methods
    public:
        using BaseTerminal::SetCursorPosition;
    };
}