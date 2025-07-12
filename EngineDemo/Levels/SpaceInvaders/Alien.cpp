#include "Alien.h"
#include "TimeHelper.h"
#include "AudioManager.h"
#include "EnemyProjectile.h"
#include "Simulation.h"

using std::shared_ptr;
using Engine::Direction;

namespace SpaceInvaders
{
	void Alien::OnDestroy()
	{
		Enemy::OnDestroy();
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/AlienDeath2.wav");
		OnDestroyEvent.Notify(std::dynamic_pointer_cast<Collider>(shared_from_this()));
	}

	void Alien::Shot()
	{
		shared_ptr<EnemyProjectile> projectile = std::make_shared<EnemyProjectile>(GetMidPosX(), GetPosY() - 2, Direction::down, PROJECTILE_SPEED);
		Engine::Simulation::Instance().TryAddEntity(projectile);
	}

	void Alien::Update()
	{
		bool showFirstAnimFrameNew = Engine::TimeHelper::Instance().IsTimeForFirstOfTwoModels(1);
		if (isFirsAnimationFrameTime != showFirstAnimFrameNew)
		{
			StepAnimation();
			isFirsAnimationFrameTime = showFirstAnimFrameNew;
		}
	}
}