#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienLowScore : public Alien
	{
	private:
		static const Engine::Model kModel1;
		static const Engine::Model kModel2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		size_t GetScore() const override { return 10; }
		Engine::TerminalColor GetColor() const override { return Engine::color::kYellowDark; }

	protected:
		void InitModel() override
		{
			animation_model_1_ = &kModel1;
			animation_model_2_ = &kModel2;
			SetModel(kModel1);
		}

	};

	const Engine::Model AlienLowScore::kModel1
	(
		4,
		{
			'[', ':', ':', ']',
			'/', '"', '"', '\\'
		}
	);

	const Engine::Model AlienLowScore::kModel2
	(
		4,
		{
			'[', '.', '.', ']',
			'\\', '"', '"', '/'
		}
	);
}