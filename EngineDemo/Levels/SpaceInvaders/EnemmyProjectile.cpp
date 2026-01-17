#include "EnemyProjectile.h"
#include "PlayerTank.h"

using std::shared_ptr;
using Engine::Direction;
using Engine::Model;

namespace SpaceInvaders
{
	const Model EnemyProjectile::kModel(1, { '|' });

	void EnemyProjectile::OnCollisionEnter(shared_ptr<Collider> other, Direction collision_dir)
	{
		Projectile::OnCollisionEnter(other, collision_dir);

		shared_ptr<PlayerTank> other_tank = std::dynamic_pointer_cast<PlayerTank>(other);
		if (other_tank != nullptr)
			other_tank->TakeDamage();
	}
}