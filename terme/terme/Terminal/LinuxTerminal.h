#pragma once
#include <terme/Terminal/BaseTerminal.h>
#include <nbase_kit/singleton.h>

namespace Engine
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
        void SetCursorPosition(const Vector2Int& position) override;

    protected:
        void HideCursor() override;

    //================================================================= Methods
    public:
        using BaseTerminal::SetCursorPosition;
    };
}