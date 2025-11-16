#pragma once
#include "BaseTerminal.h"
#include "General/Singleton.h"

namespace Engine
{
    class LinuxTerminal : public Singleton<LinuxTerminal>, public BaseTerminal
    {
        friend class Singleton<LinuxTerminal>;

        //================================================================= Fields
        static constexpr const char* CLEAR_TERMINAL = "\033[2J\033[3J";

    //================================================================= Override Methods
    public:
        void Clear() override;
        void SetCursorPosition(const Vector2Int& position) override;

    protected:
        void HideCursor() override { std::cout << "\033[?25l"; };

    //================================================================= Methods
    public:
        using BaseTerminal::SetCursorPosition;
    };
}