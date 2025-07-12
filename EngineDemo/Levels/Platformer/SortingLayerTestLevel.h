#pragma once
#include "Level.h"

namespace Platformer
{
    class SortingLayerTestLevel : public Engine::Level
    {
        //---------------------------------------------------------- Methods
    public:
        int GetWorldSizeX() const override { return 100; }
        int GetWorldSizeY() const override { return 30; }
        int GetScreenPadding() const override { return 1; }
        double ShowGameOverScreenDelay()const { return 0; }

        void LoadInSimulation() override;
    };
}