#pragma once
#include "Enemy.h"
#include "Terminal/Terminal.h"
#include "Utils/DirectionUtils.h"
#include <array>

namespace SpaceInvaders
{
	class Ufo : public Enemy
	{
		//------------------------------------------------------ Fields
	private:
		static const Engine::Model model_1;
		static inline constexpr std::array<size_t, 6> kPossibleScores = { 50,100,150,200,250,300 };
		static constexpr size_t kMoveSpeed = 8;

		Engine::Direction move_direction_;
		//------------------------------------------------------ Methods
	public:
		Ufo(int x_pos, int y_pos, Engine::Direction move_direction) : Enemy(x_pos, y_pos), move_direction_(move_direction) {};

		bool CanExitScreenSpace() const override { return true; }
		Engine::TerminalColor GetColor() const override { return Engine::color::kRed; }
		void InitModel() override { SetModel(model_1); }
		size_t GetScore() const override;

	protected:
		void Update() override;
		void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir) override;
		Engine::TerminalColor GetDestroyedParticlesColor() override { return Engine::color::kRed; }
	};
}