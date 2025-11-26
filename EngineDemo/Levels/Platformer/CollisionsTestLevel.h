#pragma once
#include "SimEntities/Level.h"

namespace Platformer
{
    class CollisionsTestLevel : public Engine::Level
    {
        //---------------------------------------------------------- Methods
    public:
        int GetWorldSizeX() const override { return 800; }
        int GetWorldSizeY() const override { return 180; }
        int GetScreenPadding() const override { return 4; }
        void LoadInSimulation() override;
        double ShowGameOverScreenDelay()const override { return 0; }
    };
}