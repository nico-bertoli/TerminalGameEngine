#pragma once
#include "Level.h"
#include "Config.h"

namespace Pong
{
    class PongLevel : public Engine::Level
    {
        //---------------------------------------------------------- Methods
    private:
        static size_t scorePlayer1;
        static size_t scorePlayer2;
        //---------------------------------------------------------- Methods
    public:
        int GetWorldSizeX() const override { return 50; }
        int GetWorldSizeY() const override { return 35; }
        int GetScreenPadding() const override { return 2; }
        void LoadInSimulation() override;
        void IncreaseP1Score();
        void IncreaseP2Score();

    protected:
        double ShowGameOverScreenDelay() const override { return 0.5; }
        void OnPostGameOverDelayEnded() override;
        void OnGameOver() override;

    private:
        void RefreshHeader();
    };
}