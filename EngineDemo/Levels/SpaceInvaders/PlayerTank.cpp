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
    void PlayerTank::Update()
    {
        if (Engine::Simulation::Instance().GetActiveLevel()->IsGameOver())
            return;

        HandleMovement();
        HandleShooting();
    }

    void PlayerTank::HandleMovement()
    {
        if (Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kA) || Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kArrowLeft))
            TryMove(Direction::kLeft, kMoveSpeed);
        else if (Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kD) || Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kArrowRight))
            TryMove(Direction::kRight, kMoveSpeed);
    }

    void PlayerTank::HandleShooting()
    {
        if (level_->IsLoadingWave())
            return;

        if (Engine::InputManager::Instance().IsKeyPressed(Engine::Key::kSpace))
        {
            double time = Engine::TimeManager::Instance().GetTime();

#if CHEAT_SPACEINV_FAST_FIRE
            if (time - last_time_shot_ > 0.08)
                last_time_shot_ = -99;
#endif

            if (time - last_time_shot_ > kShotsDelay)
            {
                last_time_shot_ = Engine::TimeManager::Instance().GetTime();
                shared_ptr<PlayerProjectile> projectile = std::make_shared<PlayerProjectile>(GetMidPosX(), GetMaxPosY() + 1, Direction::kUp, kProjectileSpeed);
                Engine::Simulation::Instance().TryAddEntity(projectile);
                Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/Shot1.wav");
            }
        }
    }

    void PlayerTank::TakeDamage()
    {
#if !CHEAT_SPACEINV_INVINCIBILITY
        health_--;
        on_damage_taken.Notify(health_);

        if (health_ > 0)
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/DamageTaken.wav");
#endif
    }
}