#include "EnemyProjectile.h"
#include "PlayerTank.h"

using std::shared_ptr;
using Engine::Direction;
using Engine::Model;

namespace SpaceInvaders
{
	const Model EnemyProjectile::MODEL(1, { '|' });

	void EnemyProjectile::OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
	{
		Projectile::OnCollisionEnter(other, collisionDir);

		shared_ptr<PlayerTank> otherTank = std::dynamic_pointer_cast<PlayerTank>(other);
		if (otherTank != nullptr)
			otherTank->TakeDamage();
	}
}