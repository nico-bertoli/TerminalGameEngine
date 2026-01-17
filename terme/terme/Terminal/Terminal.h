#pragma once
#include <terme/Config.h>

 #if IS_LINUX_BUILD
    #include <terme/Terminal/LinuxTerminal.h>
 #else
    #include <terme/Terminal/WindowsTerminal.h>
 #endif

namespace Engine
{
    #if IS_LINUX_BUILD
        using Terminal = LinuxTerminal;
    #else
        using Terminal = WindowsTerminal;
    #endif
}