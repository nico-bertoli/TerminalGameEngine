#pragma once
#include "SimEntities/StaticCollider.h"

namespace SpaceInvaders
{
    class ShieldPart : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    private:
        Engine::Model model = CreteModelUsingChar('=', 1, 1);

        //---------------------------------------------------------- Methods
    public:
        using Collider::Collider;

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::Color::GREEN; }
        void InitModel() override { SetModel(model); }
        void OnCollisionEnter(std::shared_ptr<Collider>other, Engine::Direction collisionDir)override;
    };
}