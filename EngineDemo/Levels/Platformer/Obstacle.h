#pragma once
#include "SimEntities/MovingStraightObject.h"

namespace Platformer
{
    class Obstacle : public Engine::MovingStraightObject
    {
    private:
        static Engine::Model model_;
        //---------------------------------------------------------- Methods
    public:
        using MovingStraightObject::MovingStraightObject;

        bool CanExitScreenSpace() const override { return true; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::color::kRed; }

    protected:
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir) override;
        void InitModel() override;
    };
}