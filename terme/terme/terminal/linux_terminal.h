#pragma once
#include <terme/terminal/base_terminal.h>
#include <nbase_kit/singleton.h>

namespace terme
{
    class linux_terminal : public nbase_kit::Singleton<linux_terminal>, public base_terminal
    {
        friend class nbase_kit::Singleton<linux_terminal>;

        //================================================================= Fields
        static constexpr const char* kClearTerminal = "\033[2J\033[3J";

    //================================================================= Constructor/Destructor
    protected:
        linux_terminal();

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