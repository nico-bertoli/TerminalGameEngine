#include "DebugPrinter.h"

using std::string;

namespace Engine
{
    void DebugPrinter::PrintCoutCallsCount(size_t coutCallsCount)
    {
        int startingColor = Terminal::Instance().GetColor();
        COORD cursorStartingPos = terminal.GetCursorPosition();

        Terminal::Instance().SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + POSITION_COUT_CALLS);
        //final space makes sure old string is cleared
        string output = "COUT CALLS: " + std::to_string(coutCallsCount) + string("     ");
        std::cout << output;

        terminal.SetCursorPosition(cursorStartingPos);
        terminal.SetColor(startingColor);
    }

    void DebugPrinter::PrintFpsString(size_t fps)
    {
        terminal.SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + FPS_POSITION);
        string output = "FPS: " + std::to_string(fps) + '\n';
        std::cout << output;
    }

    void DebugPrinter::PrintGenericLog(const string& log, int lineIndex)
    {
        terminal.SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + GENERIC_LOG_POSITION + lineIndex);
        std::cout << log;
    }
}