#pragma once
#include <terme/terminal/base_terminal.h>
#include <nbase_kit/singleton.h>

namespace terme
{
    class LinuxTerminal : public nbase_kit::Singleton<LinuxTerminal>, public BaseTerminal
    {
        friend class nbase_kit::Singleton<LinuxTerminal>;

        //================================================================= Fields
        static constexpr const char* kClearTerminal = "\033[2J\033[3J";

    //================================================================= Constructor/Destructor
    protected:
        LinuxTerminal();

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