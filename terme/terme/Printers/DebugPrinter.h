#pragma once
#include <terme/Printers/Printer.h>
#include <terme/Terminal/Terminal.h>

#include <iostream>
#include <string>

namespace Engine
{
    class DebugPrinter : public Printer
    {
        //------------------------------------------ Settings
    private:
        static constexpr TerminalColor kDebugColor = color::kCyan;
        static constexpr size_t kFpsPosition = 1;
        static constexpr size_t kPositoinCoutCalls = 2;
        static constexpr size_t kGenericLogPosition = 3;

        //------------------------------------------ Methodss
    public:
        using Printer::Printer;

    public:
        void PrintCoutCallsCount(size_t cout_calls_count);
        void PrintFpsString(size_t fps);
        void PrintGenericLog(const std::string& log, int line_index);

    };
}