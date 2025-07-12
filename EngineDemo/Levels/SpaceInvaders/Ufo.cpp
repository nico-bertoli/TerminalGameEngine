#include "Ufo.h"
#include "RandomUtils.h"
#include "AudioManager.h"

using Engine::Model;
using Engine::Direction;
using std::shared_ptr;

namespace SpaceInvaders
{
	const std::array<size_t, 6> Ufo::POSSIBLE_SCORES = { 50,100,150,200,250,300 };

	const Model Ufo::MODEL_1
	(
		4,
		{
			'/', '(', ')', '\\',
			'\\', '_', '_', '/'
		}
	);

	size_t Ufo::GetScore() const
	{
		int randomIndex = RandomUtils::GetRandomInt(0, static_cast<int>(POSSIBLE_SCORES.size() - 1));
		return POSSIBLE_SCORES[randomIndex];
	}

	void Ufo::Update()
	{
		TryMove(moveDirection, MOVE_SPEED);
	}

	void Ufo::OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
	{
		Enemy::OnCollisionEnter(other, collisionDir);
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/UfoDefeated.wav");
	}

}