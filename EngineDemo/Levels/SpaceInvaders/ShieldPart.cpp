#include "ShieldPart.h"
#include "Simulation.h"
#include "Alien.h"
#include "Projectile.h"
#include "AudioManager.h"

using std::shared_ptr;
using Engine::Direction;

namespace SpaceInvaders
{
    void ShieldPart::OnCollisionEnter(shared_ptr<Collider>other, Direction collisionDir)
    {
        Collider::OnCollisionEnter(other, collisionDir);

        shared_ptr<Projectile> otherProjectile = std::dynamic_pointer_cast<Projectile>(other);
        if (otherProjectile != nullptr)
        {
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/ShieldBreak.wav");
            Engine::Simulation::Instance().RemoveEntity(shared_from_this());
            return;
        }

        shared_ptr<Alien> otherAlien = std::dynamic_pointer_cast<Alien>(other);
        if (otherAlien != nullptr)
        {
            Engine::Simulation::Instance().RemoveEntity(shared_from_this());
            return;
        }
    }
}