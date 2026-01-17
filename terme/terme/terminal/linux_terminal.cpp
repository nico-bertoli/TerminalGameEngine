#include <terme/config.h>

#if IS_LINUX_BUILD

#include <terme/terminal/terminal.h>
#include <terme/managers/debug_manager.h>

#include <iostream>
#include <string>
#include <unistd.h> 
#include <termios.h>

using std::cout;

namespace terme
{
    linux_terminal::linux_terminal()
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

    void linux_terminal::HideCursor()
    {
        std::cout << "\033[?25l";
        std::cout.flush();
    }

    void linux_terminal::Clear()
    {
        cout << kClearTerminal;
        cout << "\033[2J\033[H"; //apply bg color
        SetCursorPosition(0, 0);
        HideCursor();
    }

    void linux_terminal::SetCursorPosition(const vector2_int& position)
    {
        printf("\033[%d;%dH", position.Y + 1, position.X + 1);
    }
}

#endif //IS_LINUX_BUILD
