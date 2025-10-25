#pragma once
#include "MovingStraightObject.h"

namespace Platformer
{
    class Obstacle : public Engine::MovingStraightObject
    {
    private:
        static Engine::Model model;
        //---------------------------------------------------------- Methods
    public:
        using MovingStraightObject::MovingStraightObject;

        bool CanExitScreenSpace() const override { return true; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::TerminalColor::RED; }

    protected:
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
        void InitModel() override;
    };
}