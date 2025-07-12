#pragma once
#include "Printer.h"
#include "Frame.h"

namespace Engine
{
    class UIPrinter : public Printer
    {
        //---------------------------------------------------------- Fields

    public:
        enum class WindowPosition { CenterX_TopY, CenterX_CenterY };

    private:
        static const char MARGIN_HORIZONTAL_CHAR = '=';
        static const char MARGIN_VERTICAL_CHAR = '|';

        //---------------------------------------------------------- Methods
    public:
        UIPrinter(size_t screenSizeX, size_t screenSizeY, size_t screenPadding, int marginsColor);
        void PrintWindow(const Frame& window, int color, WindowPosition windowPosition);
        void PrintOnHeader(const std::string& header, int xPos, int color);

    private:
        void DrawMargins(int color);
        void DrawHorizontalMargin();
    };
}