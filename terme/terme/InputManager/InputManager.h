#pragma once
#include <terme/Config.h>

 #if IS_LINUX_BUILD
    #include <terme/InputManager/LinuxInputManager.h>
 #else
    #include <terme/InputManager/WindowsInputManager.h>
 #endif

namespace Engine
{
    #if IS_LINUX_BUILD
        using InputManager = LinuxInputManager;
    #else
        using InputManager = WindowsInputManager;
    #endif
}
