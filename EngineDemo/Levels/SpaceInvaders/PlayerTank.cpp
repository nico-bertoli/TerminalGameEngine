#include "PlayerTank.h"
#include "Core/Simulation.h"
#include "InputManager/InputManager.h"
#include "PlayerProjectile.h"
#include "Managers/TimeManager.h"
#include "SimEntities/Level.h"
#include "Managers/AudioManager.h"
#include "SpaceInvadersLevel.h"

using Engine::Direction;
using Engine::Model;
using std::shared_ptr;

namespace SpaceInvaders
{
    const Model PlayerTank::MODEL
    (
        5,
        {
            ' ', '_', '^', '_', ' ',
            '/', '_', '_', '_', '\\'
        }
    );

    void PlayerTank::Update()
    {
        if (Engine::Simulation::Instance().GetActiveLevel()->IsGameOver())
            return;

        HandleMovement();
        HandleShooting();
    }

    void PlayerTank::HandleMovement()
    {
        if (Engine::InputManager::Instance().IsKeyPressed(Engine::Key::A) || Engine::InputManager::Instance().IsKeyPressed(Engine::Key::ARROW_LEFT))
            TryMove(Direction::left, MOVE_SPEED);
        else if (Engine::InputManager::Instance().IsKeyPressed(Engine::Key::D) || Engine::InputManager::Instance().IsKeyPressed(Engine::Key::ARROW_RIGHT))
            TryMove(Direction::right, MOVE_SPEED);
    }

    void PlayerTank::HandleShooting()
    {
        if (level->IsLoadingWave())
            return;

        if (Engine::InputManager::Instance().IsKeyPressed(Engine::Key::SPACE))
        {
            double time = Engine::TimeManager::Instance().GetTime();

#if CHEAT_SPACEINV_FAST_FIRE
            if (time - lastTimeShot > 0.08)
                lastTimeShot = -99;
#endif

            if (time - lastTimeShot > SHOTS_DELAY)
            {
                lastTimeShot = Engine::TimeManager::Instance().GetTime();
                shared_ptr<PlayerProjectile> projectile = std::make_shared<PlayerProjectile>(GetMidPosX(), GetMaxPosY() + 1, Direction::up, PROJECTILE_SPEED);
                Engine::Simulation::Instance().TryAddEntity(projectile);
                Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/Shot1.wav");
            }
        }
    }

    void PlayerTank::TakeDamage()
    {
#if !CHEAT_SPACEINV_INVINCIBILITY
        health--;
        OnDamageTaken.Notify(health);

        if (health > 0)
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/DamageTaken.wav");
#endif
    }
}