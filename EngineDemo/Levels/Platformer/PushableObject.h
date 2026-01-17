#pragma once
#include "SimEntities/Collider.h"
#include "Bunny.h"
#include "Managers/AudioManager.h"

namespace Platformer
{
    class PushableObject : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    private:
        Engine::Model model_ = CreteModelUsingChar('@', 4, 2);
        //---------------------------------------------------------- Methods
    public:
        using Collider::Collider;
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 8; }
        Engine::TerminalColor GetColor() const override { return Engine::color::kBlue; }

    protected:
        void InitModel() override { SetModel(model_); }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir)override
        {
            if (collision_dir == Engine::Direction::kRight || collision_dir == Engine::Direction::kLeft)
            {
                TryMove(DirectionUtils::GetInverseDirection(collision_dir), 9999);
                collisions_[collision_dir].clear();
            }
            else
            {
                if(std::dynamic_pointer_cast<Bunny>(other))
                   Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/Hit.wav", 0.2);
            }
        }
    };
}