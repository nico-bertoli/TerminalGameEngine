#include "Config.h"

#if IS_LINUX_BUILD

#include "Terminal.h"
#include "Managers/DebugManager.h"

#include <iostream>
#include <string>
#include <unistd.h> 
#include <termios.h>

using std::cout;

namespace Engine
{
    void LinuxTerminal::Clear()
    {
        cout << CLEAR_TERMINAL;
        SetCursorPosition(0, 0);
    }

    void LinuxTerminal::SetColor(TerminalColor color)
    {
        const char* linuxColor = ToLinuxColor(color);
        currentColor = color;
        cout << linuxColor;
    }

    void LinuxTerminal::SetCursorPosition(const Vector2Int& position)
    {
        printf("\033[%d;%dH", position.Y + 1, position.X + 1);
    }

    Vector2Int LinuxTerminal::GetCursorPosition()
    {
        struct termios oldt, raw;
        tcgetattr(STDIN_FILENO, &oldt);
        raw = oldt;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);

        std::cout << "\033[6n" << std::flush;

        int row = 1, col = 1;
        char ch;
        char buf[32];
        int i = 0;

        while (i < (int)sizeof(buf) - 1 && read(STDIN_FILENO, &ch, 1) == 1) {
            buf[i++] = ch;
            if (ch == 'R') break;
        }
        buf[i] = '\0';

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        if (buf[0] == '\033' && buf[1] == '[')
            sscanf(buf + 2, "%d;%d", &row, &col);

        return Vector2Int(col - 1, row - 1);
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
                return RESET_COLOR;
        }
    }
}

#endif //IS_LINUX_BUILD
