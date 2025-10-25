#include "Config.h"

#if !IS_LINUX_BUILD

#include "BaseTerminal.h"
#include "Managers/DebugManager.h"

#include <iostream>
#include <string>
#include <windows.h>

using string = std::string;

namespace Engine
{
    const int WindowsTerminal::WHITE_DARK = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
    const int WindowsTerminal::RED_DARK = FOREGROUND_RED;
    const int WindowsTerminal::GREEN_DARK = FOREGROUND_GREEN;
    const int WindowsTerminal::BLUE_DARK = FOREGROUND_BLUE;
    const int WindowsTerminal::CYAN_DARK = FOREGROUND_GREEN | FOREGROUND_BLUE;
    const int WindowsTerminal::MAGENTA_DARK = FOREGROUND_RED | FOREGROUND_BLUE;
    const int WindowsTerminal::YELLOW_DARK = FOREGROUND_RED | FOREGROUND_GREEN;
    const int WindowsTerminal::BLACK = 0;

    const int WindowsTerminal::WHITE = WHITE_DARK | FOREGROUND_INTENSITY;
    const int WindowsTerminal::RED = RED_DARK | FOREGROUND_INTENSITY;
    const int WindowsTerminal::GREEN = GREEN_DARK | FOREGROUND_INTENSITY;
    const int WindowsTerminal::BLUE = BLUE_DARK | FOREGROUND_INTENSITY;
    const int WindowsTerminal::CYAN = CYAN_DARK | FOREGROUND_INTENSITY;
    const int WindowsTerminal::MAGENTA = MAGENTA_DARK | FOREGROUND_INTENSITY;
    const int WindowsTerminal::YELLOW = YELLOW_DARK | FOREGROUND_INTENSITY;
    const int WindowsTerminal::GREY = BLACK | FOREGROUND_INTENSITY;

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

        SetCursorPosition(coord);
    }

    void WindowsTerminal::SetColor(TerminalColor color)
    {
        int windowsColor = ConvertToWindowsColor(color);
        currentColor = color;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    void WindowsTerminal::SetCursorPosition(const Vector2& position)
    {
        COORD coord;
        coord.X = static_cast<short>(position.x);
        coord.Y = static_cast<short>(position.y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    Vector2 WindowsTerminal::GetCursorPosition()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD coord = { -1, -1 };  // Default to invalid position
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        {
            coord = csbi.dwCursorPosition;
        }
        return Vector2(coord.x,coord.y);
    }

    void WindowsTerminal::HideCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false; // Hide cursor
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    int WindowsTerminal::ConvertToWindowsColor(TerminalColor color)const
    {
        return WHITE; //todo implement
    }
}

#endif //!IS_LINUX_BUILD