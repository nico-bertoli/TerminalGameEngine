#pragma once
#include "Printer.h"
#include "Terminal.h"

#include <iostream>
#include <string>

namespace Engine
{
    class DebugPrinter : public Printer
    {
        //------------------------------------------ Settings
    private:
        const int DEBUG_COLOR = Terminal::CYAN;
        const size_t FPS_POSITION = 1;
        const size_t POSITION_COUT_CALLS = 2;
        const size_t GENERIC_LOG_POSITION = 3;

        //------------------------------------------ Methodss
    public:
        using Printer::Printer;

    public:
        void PrintCoutCallsCount(size_t coutCallsCount);
        void PrintFpsString(size_t fps);
        void PrintGenericLog(const std::string& log, int lineIndex);

    };
}