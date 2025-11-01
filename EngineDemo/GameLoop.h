#pragma once

#include "SimEntities/Level.h"

class GameLoop
{
    //---------------------------------------------------------- Methods
public:
    GameLoop();
private:
    std::shared_ptr<Engine::Level> ShowLevelSelection();
    bool LoopSimulation(std::shared_ptr<Engine::Level> level);
};