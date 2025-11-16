#pragma once
#include "BaseTerminal.h"
#include "General/Singleton.h"
#include "General/Vector2D.h"

namespace Engine
{
    class WindowsTerminal : public Singleton<WindowsTerminal>, public BaseTerminal
    {
        friend class Singleton<WindowsTerminal>;

    //================================================================= Fields
    private:    
        //colors
        const static int WHITE_DARK;
        const static int RED_DARK;
        const static int GREEN_DARK;
        const static int BLUE_DARK;
        const static int CYAN_DARK;
        const static int MAGENTA_DARK;
        const static int YELLOW_DARK;

        const static int WHITE;
        const static int RED;
        const static int GREEN;
        const static int BLUE;
        const static int CYAN;
        const static int MAGENTA;
        const static int YELLOW;
        const static int GREY;
        const static int BLACK;

    //================================================================= Override Methods
    public:
        void Clear() override;
        void SetColor(TerminalColor color) override;
        TerminalColor GetColor() override { return currentColor; };
        void SetCursorPosition(const Vector2Int& position) override;
        Vector2Int GetCursorPosition() override;

    protected:
        void HideCursor() override;

    //================================================================= Methods
    public:
        using BaseTerminal::SetCursorPosition;

    protected:
        int ConvertToWindowsColor(TerminalColor genericColor)const;
    };
}