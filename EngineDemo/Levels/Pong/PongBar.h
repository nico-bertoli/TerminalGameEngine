#pragma once
#include "VariableSizeCollider.h"

namespace Pong
{
    class PongBar : public Engine::VariableSizeCollider
    {
        //---------------------------------------------------------- Fields
    private:
        double moveSpeed;
        bool isBottomBar;
        double deflectBallFactor;

        //---------------------------------------------------------- Methods
    public:
        PongBar
        (
            int xPos,
            int yPos,
            size_t sizeX,
            size_t sizeY,
            char modelChar,
            double moveSpeed,
            double deflectBallFactor,
            bool isBottomBar
        );

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::TerminalColor::CYAN; }

        double GetDeflectBallFactor() { return deflectBallFactor; }

    protected:
        void Update() override;
    };
}