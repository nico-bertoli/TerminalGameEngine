#pragma once
#include "BaseTerminal.h"
#include <NbaseKit/Singleton.h>

namespace Engine
{
    class LinuxTerminal : public NbaseKit::Singleton<LinuxTerminal>, public BaseTerminal
    {
        friend class NbaseKit::Singleton<LinuxTerminal>;

        //================================================================= Fields
        static constexpr const char* CLEAR_TERMINAL = "\033[2J\033[3J";

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