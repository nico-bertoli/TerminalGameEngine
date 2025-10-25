#include "Config.h"

#if IS_LINUX_BUILD

#include "Terminal.h"
#include "Debug/DebugManager.h"

#include <iostream>
#include <string>
#include <unistd.h> 
#include <termios.h>

using std::cout;

namespace Engine
{
    void LinuxTerminal::Clear()
    {
        cout << "\033[2J\033[1;1H";
        cout.flush();
    }

    void LinuxTerminal::SetColor(TerminalColor color)
    {
        const char* linuxColor = ToLinuxColor(color);
        cout<<linuxColor;
    }

    void LinuxTerminal::SetCursorPosition(const Vector2Int& position)
    {
        // std::cout << "\033[10;5H"    <--- sets cursor at 10-5

        std::string setCursorPositionStr;
        setCursorPositionStr.reserve(32); // optional but good
        setCursorPositionStr.append("\033[");
        setCursorPositionStr.append(std::to_string(position.X));
        setCursorPositionStr.append(";");
        setCursorPositionStr.append(std::to_string(position.Y));
        setCursorPositionStr.append("H");

        cout<<setCursorPositionStr;
    }

    Vector2Int LinuxTerminal::GetCursorPosition()
    {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // turn off canonical mode and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        std::cout << "\033[6n" << std::flush; // request cursor position

        int row = 0, col = 0;
        char ch;
        std::string response;

        while (read(STDIN_FILENO, &ch, 1) == 1) {
            if (ch == 'R') break;
            response += ch;
        }

        // response format: ESC[row;col
        if (response[0] == '\033' && response[1] == '[') {
            sscanf(response.c_str(), "\033[%d;%d", &row, &col);
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return Vector2Int(row,col);
    }

    const char* LinuxTerminal::ToLinuxColor(TerminalColor color)
    {
        switch (color)
        {
            case TerminalColor::BLACK:          return BLACK;
            case TerminalColor::RED_DARK:       return RED_DARK;
            case TerminalColor::GREEN_DARK:     return GREEN_DARK;
            case TerminalColor::YELLOW_DARK:    return YELLOW_DARK;
            case TerminalColor::BLUE_DARK:      return BLUE_DARK;
            case TerminalColor::MAGENTA_DARK:   return MAGENTA_DARK;
            case TerminalColor::CYAN_DARK:      return CYAN_DARK;
            case TerminalColor::WHITE_DARK:     return WHITE_DARK;

            case TerminalColor::GREY:           return GREY;
            case TerminalColor::RED:            return RED;
            case TerminalColor::GREEN:          return GREEN;
            case TerminalColor::YELLOW:         return YELLOW;
            case TerminalColor::BLUE:           return BLUE;
            case TerminalColor::MAGENTA:        return MAGENTA;
            case TerminalColor::CYAN:           return CYAN;
            case TerminalColor::WHITE:          return WHITE;

            default:
                return RESET;
        }
    }
}

#endif //IS_LINUX_BUILD