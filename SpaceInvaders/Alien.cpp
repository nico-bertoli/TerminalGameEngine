#include "Alien.h"
#include "TimeHelper.h"
#include "AudioManager.h"
#include "EnemyProjectile.h"
#include "Simulation.h"

namespace SpaceInvaders
{
	void Alien::OnDestroy()
	{
		Enemy::OnDestroy();
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/AlienDeath2.wav");
		OnDestroyEvent.Notify(this);
	}

	void Alien::Shot()
	{
		EnemyProjectile* projectile = new EnemyProjectile(GetMidPosX(), GetPosY() - 2, Direction::down, PROJECTILE_SPEED);
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