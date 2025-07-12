#include "Terminal.h"
#include "DebugManager.h"
#include <iostream>
#include <string>

using string = std::string;

namespace Engine
{

    const int Terminal::WHITE_DARK = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
    const int Terminal::RED_DARK = FOREGROUND_RED;
    const int Terminal::GREEN_DARK = FOREGROUND_GREEN;
    const int Terminal::BLUE_DARK = FOREGROUND_BLUE;
    const int Terminal::CYAN_DARK = FOREGROUND_GREEN | FOREGROUND_BLUE;
    const int Terminal::MAGENTA_DARK = FOREGROUND_RED | FOREGROUND_BLUE;
    const int Terminal::YELLOW_DARK = FOREGROUND_RED | FOREGROUND_GREEN;
    const int Terminal::BLACK = 0;

    const int Terminal::WHITE = WHITE_DARK | FOREGROUND_INTENSITY;
    const int Terminal::RED = RED_DARK | FOREGROUND_INTENSITY;
    const int Terminal::GREEN = GREEN_DARK | FOREGROUND_INTENSITY;
    const int Terminal::BLUE = BLUE_DARK | FOREGROUND_INTENSITY;
    const int Terminal::CYAN = CYAN_DARK | FOREGROUND_INTENSITY;
    const int Terminal::MAGENTA = MAGENTA_DARK | FOREGROUND_INTENSITY;
    const int Terminal::YELLOW = YELLOW_DARK | FOREGROUND_INTENSITY;
    const int Terminal::GREY = BLACK | FOREGROUND_INTENSITY;

    void Terminal::Clear()
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

    void Terminal::SetColor(int color)
    {
        currentColor = color;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    void Terminal::SetCursorPosition(size_t x, size_t y)
    {
        COORD coord;
        coord.X = static_cast<short>(x);
        coord.Y = static_cast<short>(y);
        SetCursorPosition(coord);
    }

    void Terminal::SetCursorPosition(const COORD& coord)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    COORD Terminal::GetCursorPosition()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD coord = { -1, -1 };  // Default to invalid position
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        {
            coord = csbi.dwCursorPosition;
        }
        return coord;
    }

    void Terminal::HideCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false; // Hide cursor
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void Terminal::Cout(const string& s) const
    {
        std::cout << s;

#if DEBUG_MODE && SHOW_COUT_CALLS
        DebugManager::Instance().IncrementCoutCalls();
#endif
    }

    void Terminal::Cout(char c) const
    {
        std::cout << c;

#if DEBUG_MODE && SHOW_COUT_CALLS
        DebugManager::Instance().IncrementCoutCalls();
#endif
    }
}