#include "PlayerProjectile.h"
#include "Simulation.h"
#include "Enemy.h"
#include "SpaceInvadersLevel.h"

using Engine::Model;
using std::shared_ptr;
using Engine::Direction;

namespace SpaceInvaders
{
	const Model PlayerProjectile::MODEL(1, { '|' });

	void PlayerProjectile::OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
	{
		Projectile::OnCollisionEnter(other, collisionDir);
		shared_ptr<Enemy> otherEnemy = std::dynamic_pointer_cast<Enemy>(other);
		if (otherEnemy != nullptr)
		{
			Engine::Simulation::Instance().RemoveEntity(otherEnemy);
		}
	}
}
