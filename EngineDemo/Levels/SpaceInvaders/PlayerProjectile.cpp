#include "PlayerProjectile.h"
#include "Core/Simulation.h"
#include "Enemy.h"
#include "SpaceInvadersLevel.h"

using Engine::Model;
using std::shared_ptr;
using Engine::Direction;

namespace SpaceInvaders
{
	void PlayerProjectile::OnCollisionEnter(shared_ptr<Collider> other, Direction collision_dir)
	{
		Projectile::OnCollisionEnter(other, collision_dir);
		shared_ptr<Enemy> other_enemy = std::dynamic_pointer_cast<Enemy>(other);
		if (other_enemy != nullptr)
		{
			Engine::Simulation::Instance().RemoveEntity(other_enemy);
		}
	}
}
