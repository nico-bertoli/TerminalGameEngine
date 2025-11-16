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
        Engine::Model model = CreteModelUsingChar('@', 4, 2);
        //---------------------------------------------------------- Methods
    public:
        using Collider::Collider;
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 8; }
        Engine::TerminalColor GetColor() const override { return Engine::Color::BLUE; }

    protected:
        void InitModel() override { SetModel(model); }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir)override
        {
            if (collisionDir == Engine::Direction::right || collisionDir == Engine::Direction::left)
            {
                TryMove(DirectionUtils::GetInverseDirection(collisionDir), 9999);
                collisions[collisionDir].clear();
            }
            else
            {
                if(std::dynamic_pointer_cast<Bunny>(other))
                   Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/Hit.wav", 0.2);
            }
        }
    };
}