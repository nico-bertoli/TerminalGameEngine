#pragma once
#include "MovingStraightObject.h"

using std::shared_ptr;
using Engine::Model;
using Engine::Direction;

namespace Platformer
{
    class Obstacle : public Engine::MovingStraightObject
    {
    private:
        static Model model;
        //---------------------------------------------------------- Methods
    public:
        using MovingStraightObject::MovingStraightObject;

        bool CanExitScreenSpace() const override { return true; }
        double GetGravityScale() const override { return 0; }
        int GetColor() const override { return Engine::Terminal::RED; }

    protected:
        void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir) override;
        void InitModel() override;
    };
}