#pragma once
#include "MovingStraightObject.h"
#include "Simulation.h"
#include "Enemy.h"
#include "ShieldPart.h"

namespace SpaceInvaders
{
    class Projectile : public Engine::MovingStraightObject
    {
        //---------------------------------------------------------- Methods
    public:
        using MovingStraightObject::MovingStraightObject;

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override
        {
            MovingStraightObject::OnCollisionEnter(other, collisionDir);
            Engine::Direction collisionOppositeDirection = DirectionUtils::GetInverseDirection(collisionDir);

            std::shared_ptr<Enemy> otherEnemy = std::dynamic_pointer_cast<Enemy>(other);
            if (otherEnemy == nullptr)
            {
                Engine::Simulation::Instance().SpawnParticles
                (
                    GetPosX(),
                    GetPosY(),
                    GetModelWidth(),
                    GetModelHeight(),
                    '*',
                    GetColor(),
                    8,     //speed
                    3,      //movement life
                    4,      //density
                    collisionOppositeDirection
                );
            }

            Engine::Simulation::Instance().RemoveEntity(shared_from_this());
        }
    };
}