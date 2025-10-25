#pragma once
#include "Enemy.h"
#include "TerminalManager.h"
#include "DirectionUtils.h"
#include <array>

namespace SpaceInvaders
{
	class Ufo : public Enemy
	{
		//------------------------------------------------------ Fields
	private:
		static const Engine::Model MODEL_1;
		static const std::array<size_t, 6> POSSIBLE_SCORES;
		static const size_t MOVE_SPEED = 8;

		Engine::Direction moveDirection;
		//------------------------------------------------------ Methods
	public:
		Ufo(int xPos, int yPos, Engine::Direction moveDirection) : Enemy(xPos, yPos), moveDirection(moveDirection) {};

		bool CanExitScreenSpace() const override { return true; }
		Engine::TerminalColor GetColor() const override { return Engine::TerminalColor::RED; }
		void InitModel() override { SetModel(MODEL_1); }
		size_t GetScore() const override;

	protected:
		void Update() override;
		void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
		Engine::TerminalColor GetDestroyedParticlesColor() override { return Engine::TerminalColor::RED; }
	};
}