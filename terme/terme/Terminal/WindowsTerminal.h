#pragma once
#include <terme/Terminal/BaseTerminal.h>
#include <nbase_kit/singleton.h>
#include <nbase_kit/matrix.h>

namespace Engine
{
    class WindowsTerminal : public nbase_kit::Singleton<WindowsTerminal>, public BaseTerminal
    {
        friend class nbase_kit::Singleton<WindowsTerminal>;

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