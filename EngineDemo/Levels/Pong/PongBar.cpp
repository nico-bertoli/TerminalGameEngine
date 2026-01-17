#include "PongBar.h"
#include "InputManager/InputManager.h"
#include "Core/Simulation.h"
#include "SimEntities/Level.h"

using Engine::Direction;

namespace Pong
{
    PongBar::PongBar
    (
        int x_pos,
        int y_pos,
        size_t size_x,
        size_t size_y,
        char model_char,
        double move_speed,
        double deflect_ball_factor,
        bool is_bottom_bar
    ) :
        VariableSizeCollider(x_pos, y_pos, size_x, size_y, model_char),
        move_speed_(move_speed),
        deflect_ball_factor_(deflect_ball_factor),
        is_bottom_bar_(is_bottom_bar)
    {
    }

    void PongBar::Update()
    {
        if (Engine::Simulation::Instance().GetActiveLevel()->IsGameOver())
            return;

        if ((is_bottom_bar_ && Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kA)) || !is_bottom_bar_ && Engine::InputManager::Instance().Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kArrowLeft))
            TryMove(Direction::kLeft, move_speed_);
        else if ((is_bottom_bar_ && Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kD)) || (!is_bottom_bar_ && Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kArrowRight)))
            TryMove(Direction::kRight, move_speed_);
    }

}