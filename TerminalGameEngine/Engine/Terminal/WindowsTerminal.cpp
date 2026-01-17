#include "Config.h"

#if !IS_LINUX_BUILD

#include "BaseTerminal.h"
#include "Managers/DebugManager.h"
#include "General/Vector2Int.h" 

#include <iostream>
#include <string>
#include <windows.h>

using string = std::string;

namespace Engine
{
    void WindowsTerminal::Clear()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = { 0, 0 };
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;

        // Get the console screen buffer info
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

        // Fill the entire screen with spaces
        FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coord, &cCharsWritten);

        // Fill the entire screen with the current attributes
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coord, &cCharsWritten);

        SetCursorPosition(coord.X,coord.Y);
    }

    void WindowsTerminal::SetCursorPosition(const Vector2Int& position)
    {
        COORD coord;
        coord.X = static_cast<short>(position.X);
        coord.Y = static_cast<short>(position.Y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void WindowsTerminal::HideCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false; // Hide cursor
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }
}

#endif //!IS_LINUX_BUILD