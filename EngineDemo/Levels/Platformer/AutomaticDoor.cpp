#include "AutomaticDoor.h"

using Direction = Engine::Direction;

namespace Platformer
{
    AutomaticDoor::AutomaticDoor
    (
        int xPos,
        int yPos,
        size_t sizeX,
        size_t sizeY,
        char modelChar,
        double moveSpeed
    ) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar), moveSpeed(moveSpeed)
    {
        startingPosY = yPos;
    }

    void AutomaticDoor::Update()
    {
        VariableSizeCollider::Update();
        if (IsOpen())
        {
            if (GetPosY() < startingPosY + GetModelHeight())
                TryMove(Direction::up, moveSpeed);
        }
        else
        {
            if (GetPosY() > startingPosY)
                TryMove(Direction::down, moveSpeed);
        }
    }

    void AutomaticDoor::RemoveEnergySource()
    {
        if (energySourcesCounter > 0)
            --energySourcesCounter;
    }
}