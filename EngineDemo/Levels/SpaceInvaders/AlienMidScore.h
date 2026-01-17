#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienMidScore : public Alien
	{
	private:
		static const Engine::Model kModel1;
		static const Engine::Model kModel2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		size_t GetScore() const override { return 20; }
		Engine::TerminalColor GetColor() const override { return Engine::color::kCyan; }

	protected:
		void InitModel() override
		{
			animation_model_1_ = &kModel1;
			animation_model_2_ = &kModel2;
			SetModel(kModel1);
		}
	};

	const Engine::Model AlienMidScore::kModel1
	(
		4,
		{
			'(', 'o', 'O', ')',
			'V', '~', '~', 'v'
		}
	);

	const Engine::Model AlienMidScore::kModel2
	(
		4,
		{
			'(', 'O', 'o', ')',
			'v', '~', '~', 'V'
		}
	);
}