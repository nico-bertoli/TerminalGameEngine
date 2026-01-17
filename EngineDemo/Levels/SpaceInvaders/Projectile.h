#pragma once
#include "SimEntities/MovingStraightObject.h"
#include "Core/Simulation.h"
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
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir) override
        {
            MovingStraightObject::OnCollisionEnter(other, collision_dir);
            Engine::Direction collision_opposite_direction = DirectionUtils::GetInverseDirection(collision_dir);

            std::shared_ptr<Enemy> other_enemy = std::dynamic_pointer_cast<Enemy>(other);
            if (other_enemy == nullptr)
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
                    collision_opposite_direction
                );
            }

            Engine::Simulation::Instance().RemoveEntity(shared_from_this());
        }
    };
}