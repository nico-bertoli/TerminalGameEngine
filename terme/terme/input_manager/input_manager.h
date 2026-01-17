#pragma once
#include <terme/config.h>

 #if IS_LINUX_BUILD
    #include <terme/input_manager/linux_input_manager.h>
 #else
    #include <terme/input_manager/windowsinput_manager.h>
 #endif

namespace terme
{
    #if IS_LINUX_BUILD
        using InputManager = LinuxInputManager;
    #else
        using InputManager = WindowsInputManager;
    #endif
}
