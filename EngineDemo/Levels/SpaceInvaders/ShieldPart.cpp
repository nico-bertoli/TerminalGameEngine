#include "ShieldPart.h"
#include "Core/Simulation.h"
#include "Alien.h"
#include "Projectile.h"
#include "Managers/AudioManager.h"

using std::shared_ptr;
using Engine::Direction;

namespace SpaceInvaders
{
    void ShieldPart::OnCollisionEnter(shared_ptr<Collider>other, Direction collision_dir)
    {
        Collider::OnCollisionEnter(other, collision_dir);

        shared_ptr<Projectile> other_projectile = std::dynamic_pointer_cast<Projectile>(other);
        if (other_projectile != nullptr)
        {
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/ShieldBreak.wav");
            Engine::Simulation::Instance().RemoveEntity(shared_from_this());
            return;
        }

        shared_ptr<Alien> other_alien = std::dynamic_pointer_cast<Alien>(other);
        if (other_alien != nullptr)
        {
            Engine::Simulation::Instance().RemoveEntity(shared_from_this());
            return;
        }
    }
}