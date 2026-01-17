#include "Ufo.h"
#include "Utils/RandomUtils.h"
#include "Managers/AudioManager.h"

using Engine::Model;
using Engine::Direction;
using std::shared_ptr;

namespace SpaceInvaders
{

	const Model Ufo::model_1
	(
		4,
		{
			'/', '(', ')', '\\',
			'\\', '_', '_', '/'
		}
	);

	size_t Ufo::GetScore() const
	{
		int random_index = RandomUtils::GetRandomInt(0, static_cast<int>(kPossibleScores.size() - 1));
		return kPossibleScores[random_index];
	}

	void Ufo::Update()
	{
		TryMove(move_direction_, kMoveSpeed);
	}

	void Ufo::OnCollisionEnter(shared_ptr<Collider> other, Direction collision_dir)
	{
		Enemy::OnCollisionEnter(other, collision_dir);
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/UfoDefeated.wav");
	}

}