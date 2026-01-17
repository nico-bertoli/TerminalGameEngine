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
    LinuxTerminal::LinuxTerminal()
    {
        struct termios newTermios;
        if (tcgetattr(STDIN_FILENO, &newTermios) == 0)
        {
            // Disable echo and canonical mode (prevents characters from being printed)
            newTermios.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
        }
        
        HideCursor();
    }

    void LinuxTerminal::HideCursor()
    {
        std::cout << "\033[?25l";
        std::cout.flush();
    }

    void LinuxTerminal::Clear()
    {
        cout << kClearTerminal;
        cout << "\033[2J\033[H"; //apply bg color
        SetCursorPosition(0, 0);
        HideCursor();
    }

    void LinuxTerminal::SetCursorPosition(const Vector2Int& position)
    {
        printf("\033[%d;%dH", position.Y + 1, position.X + 1);
    }
}

#endif //IS_LINUX_BUILD
