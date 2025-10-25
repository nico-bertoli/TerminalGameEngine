#pragma once
#include "Config.h"

 #if IS_LINUX_BUILD
    #include "LinuxInputManager.h"
 #else
    #include "WindowsInputManager.h"
 #endif

namespace Engine
{
    #if IS_LINUX_BUILD
        using InputManager = LinuxInputManager;
    #else
        using InputManager = WindowsInputManager;
    #endif
}
