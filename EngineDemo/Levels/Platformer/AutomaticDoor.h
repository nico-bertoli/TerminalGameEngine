#pragma once
#include "Config.h"
#include "SimEntities/VariableSizeCollider.h"

namespace Platformer
{

    class AutomaticDoor : public Engine::VariableSizeCollider
    {
        //---------------------------------------------------------- Fields
    private:
        double moveSpeed;
        int startingPosY;
        int energySourcesCounter = 0;

        //---------------------------------------------------------- Methods
    public:
        AutomaticDoor
        (
            int xPos,
            int yPos,
            size_t sizeX,
            size_t sizeY,
            char modelChar,
            double moveSpeed
        );

        bool IsOpen() const { return energySourcesCounter > 0; }
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const { return Engine::Color::CYAN; }
        void AddEnergySource() { ++energySourcesCounter; }
        void RemoveEnergySource();

    protected:
        void Update() override;
    };
}