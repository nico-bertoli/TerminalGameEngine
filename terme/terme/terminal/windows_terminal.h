#pragma once
#include <terme/terminal/base_terminal.h>
#include <nbase_kit/singleton.h>
#include <nbase_kit/matrix.h>

namespace terme
{
    class windows_terminal : public nbase_kit::Singleton<windows_terminal>, public base_terminal
    {
        friend class nbase_kit::Singleton<windows_terminal>;

    //================================================================= Override Methods
    public:
        void Clear() override;
        void SetCursorPosition(const vector2_int& position) override;

    protected:
        void HideCursor() override;

    //================================================================= Methods
    public:
        using base_terminal::SetCursorPosition;
    };
}