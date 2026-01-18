#pragma once
#include <terme/terminal/base_terminal.h>
#include <nbkit/singleton.h>

namespace terme
{
    class LinuxTerminal : public nbkit::Singleton<LinuxTerminal>, public BaseTerminal
    {
        friend class nbkit::Singleton<LinuxTerminal>;

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