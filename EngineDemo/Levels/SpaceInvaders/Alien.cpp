#include "Alien.h"
#include "Managers/TimeManager.h"
#include "Managers/AudioManager.h"
#include "EnemyProjectile.h"
#include "Core/Simulation.h"

using std::shared_ptr;
using Engine::Direction;

namespace SpaceInvaders
{
	void Alien::OnDestroy()
	{
		Enemy::OnDestroy();
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/AlienDeath2.wav");
		on_destroy_event.Notify(std::dynamic_pointer_cast<Collider>(shared_from_this()));
	}

	void Alien::Shot()
	{
		shared_ptr<EnemyProjectile> projectile = std::make_shared<EnemyProjectile>(GetMidPosX(), GetPosY() - 2, Direction::kDown, PROJECTILE_SPEED);
		Engine::Simulation::Instance().TryAddEntity(projectile);
	}

	void Alien::Update()
	{
		bool show_first_anim_frame_new = Engine::TimeManager::Instance().IsTimeForFirstOfTwoModels(1);
		if (is_first_animation_frame_time_ != show_first_anim_frame_new)
		{
			StepAnimation();
			is_first_animation_frame_time_ = show_first_anim_frame_new;
		}
	}
}