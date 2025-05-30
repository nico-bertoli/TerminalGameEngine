#pragma once
#include "StaticCollider.h"

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
        int GetColor() const override { return Engine::Terminal::GREEN; }
        void InitModel() override { SetModel(model); }
        void OnCollisionEnter(std::shared_ptr<Collider>other, Engine::Direction collisionDir)override;
    };
}