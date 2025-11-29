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
        cout << "\033[2J\033[H"; //apply bg color
        SetCursorPosition(0, 0);
    }

    void LinuxTerminal::SetCursorPosition(const Vector2Int& position)
    {
        printf("\033[%d;%dH", position.Y + 1, position.X + 1);
    }
}

#endif //IS_LINUX_BUILD
