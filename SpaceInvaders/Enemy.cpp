#include "Enemy.h"
#include "TimeHelper.h"
#include "Simulation.h"
#include "SpaceInvadersLevel.h"

using std::shared_ptr;

namespace SpaceInvaders
{
	void Enemy::OnDestroy()
	{
		shared_ptr<SpaceInvadersLevel> level = std::dynamic_pointer_cast<SpaceInvadersLevel>(Engine::Simulation::Instance().GetActiveLevel());
		assert(level != nullptr);
		level->IncreasePlayerScore(GetScore());
		Engine::Simulation::Instance().SpawnParticles
		(
			GetPosX(),
			GetPosY(),
			GetModelWidth(),
			GetModelHeight(),
			'*',
			GetDestroyedParticlesColor(),
			8,	//speed
			5,	//lifetime
			1.5	//density
		);
	}
}