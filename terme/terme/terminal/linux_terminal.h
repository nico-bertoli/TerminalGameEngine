#pragma once
#include <terme/terminal/base_terminal.h>
#include <nbkit/singleton.h>

namespace terme
{
    class LinuxTerminal : public nbkit::Singleton<LinuxTerminal>, public BaseTerminal
    {
        friend class nbkit::Singleton<LinuxTerminal>;

        static constexpr const char* kClearTerminal = "\033[2J\033[3J";

    protected:
        LinuxTerminal();

    public:
        void Clear() override;
        void SetCursorPosition(const vector2_int& position) override;

    protected:
        void HideCursor() override;

    public:
        using BaseTerminal::SetCursorPosition;
    };
}