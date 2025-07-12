#include "UIPrinter.h"

using std::string;

namespace Engine
{
    UIPrinter::UIPrinter(size_t screenSizeX, size_t screenSizeY, size_t screenPadding, int marginsColor) :
        Printer(screenSizeX, screenSizeY, screenPadding)
    {
        DrawMargins(marginsColor);
    };

    void UIPrinter::PrintWindow(const Frame& window, int color, WindowPosition windowPosition)
    {
        if (window.GetSizeY() == 0)
            return;

        assert(screenSizeX > window.GetSizeX());
        size_t leftwindowOffset = (screenSizeX - window.GetSizeX()) / 2;

        size_t printStartY;
        switch (windowPosition)
        {
        case WindowPosition::CenterX_CenterY:
            printStartY = screenSizeY / 2 - window.GetSizeY() / 2;
            break;

        case WindowPosition::CenterX_TopY:
            printStartY = TOP_MARGIN_SIZE;
            break;
        }

        Terminal::Instance().SetColor(color);
        for (size_t y = 0; y < window.GetSizeY(); ++y)
        {
            string line = "";
            for (size_t x = 0; x < window.GetSizeX(); ++x)
                line += window.chars.Get(x, y);

            //terminal.SetCursorPosition(leftwindowOffset + MARGIN_OFFSET_X, GetMaxTerminalY() - y - MARGIN_OFFSET_BOTTOM_Y);
            terminal.SetCursorPosition(leftwindowOffset + LEFT_MARGIN_SIZE, y + printStartY);
            terminal.Cout(line);
        }
    }

    void UIPrinter::PrintOnHeader(const string& header, int xPos, int color)
    {
        terminal.SetColor(color);
        terminal.SetCursorPosition(xPos, 0);
        terminal.Cout(header);
    }

    void UIPrinter::DrawMargins(int color)
    {
        terminal.SetColor(color);

        //horizontal
        terminal.SetCursorPosition(0, 1);
        DrawHorizontalMargin();
        terminal.SetCursorPosition(0, static_cast<int>(GetMaxTerminalY()));
        DrawHorizontalMargin();

        //vertical
        for (size_t y = TOP_MARGIN_SIZE; y < GetMaxTerminalY(); ++y)
        {
            terminal.SetCursorPosition(size_t(0), y);
            terminal.Cout(MARGIN_VERTICAL_CHAR);
            terminal.SetCursorPosition(GetMaxTerminalX(), y);
            terminal.Cout(MARGIN_VERTICAL_CHAR);
        }
    }

    void UIPrinter::DrawHorizontalMargin()
    {
        string line = "";
        for (int x = 0; x < screenSizeX + 2; ++x)
            line += MARGIN_HORIZONTAL_CHAR;
        terminal.Cout(line);
    }
}