#pragma once
#include "BaseTerminal.h"
#include <NbaseKit/Singleton.h>
#include <NbaseKit/Matrix.h>

namespace Engine
{
    class WindowsTerminal : public NbaseKit::Singleton<WindowsTerminal>, public BaseTerminal
    {
        friend class NbaseKit::Singleton<WindowsTerminal>;

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