#pragma once
#include "BaseTerminal.h"
#include "General/Singleton.h"
#include "General/Vector2D.h"

namespace Engine
{
    class WindowsTerminal : public Singleton<WindowsTerminal>, public BaseTerminal
    {
        friend class Singleton<WindowsTerminal>;

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