#pragma once
#include "Singleton.h"
#include "BaseInputManager.h"

namespace Engine
{

class LinuxInputManager : public Singleton<LinuxInputManager>, public BaseInputManager
{
public:
    inline bool IsKeyPressed(Key key)
    {
        //to be implemented
    }

    inline bool IsAnyKeyPressed()
    {
        //to be implemented
    }
};

} // namespace Engine