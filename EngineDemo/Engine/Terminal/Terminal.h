#pragma once
#include "Config.h"

 #if IS_LINUX_BUILD
    #include "LinuxTerminal.h"
 #else
    #include "WindowsTerminal.h"
 #endif

namespace Engine
{
    #if IS_LINUX_BUILD
        using Terminal = LinuxTerminal;
    #else
        using Terminal = WindowsTerminal;
    #endif
}