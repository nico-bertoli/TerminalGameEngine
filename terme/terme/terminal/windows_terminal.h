#pragma once
#include <terme/terminal/base_terminal.h>
#include <nbkit/singleton.h>
#include <nbkit/matrix.h>

namespace terme
{
    class WindowsTerminal : public nbkit::Singleton<WindowsTerminal>, public BaseTerminal
    {
        friend class nbkit::Singleton<WindowsTerminal>;

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