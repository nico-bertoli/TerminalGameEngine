#include "PongBar.h"
#include "InputManager/InputManager.h"
#include "Simulation.h"
#include "Level.h"

using Engine::Direction;

namespace Pong
{
    PongBar::PongBar
    (
        int xPos,
        int yPos,
        size_t sizeX,
        size_t sizeY,
        char modelChar,
        double moveSpeed,
        double deflectBallFactor,
        bool isBottomBar
    ) :
        VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar),
        moveSpeed(moveSpeed),
        deflectBallFactor(deflectBallFactor),
        isBottomBar(isBottomBar)
    {
    }

    void PongBar::Update()
    {
        if (Engine::Simulation::Instance().GetActiveLevel()->IsGameOver())
            return;

        if ((isBottomBar && Engine::InputManager::Instance().IsKeyPressed(Engine::Key::A)) || !isBottomBar && Engine::InputManager::Instance().Engine::InputManager::Instance().IsKeyPressed(Engine::Key::ARROW_LEFT))
            TryMove(Direction::left, moveSpeed);
        else if ((isBottomBar && Engine::InputManager::Instance().IsKeyPressed(Engine::Key::D)) || (!isBottomBar && Engine::InputManager::Instance().IsKeyPressed(Engine::Key::ARROW_RIGHT)))
            TryMove(Direction::right, moveSpeed);
    }

}