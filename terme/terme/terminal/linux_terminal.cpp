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
    LinuxTerminal::LinuxTerminal()
    {
        struct termios newTermios;
        if (tcgetattr(STDIN_FILENO, &newTermios) == 0)
        {
            // prevents characters from being printed
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

    void LinuxTerminal::SetCursorPosition(const vector2_int& position)
    {
        printf("\033[%d;%dH", position.Y + 1, position.X + 1);
    }
}

#endif