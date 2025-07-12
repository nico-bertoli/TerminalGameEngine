#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienMidScore : public Alien
	{
	private:
		static const Engine::Model MODEL_1;
		static const Engine::Model MODEL_2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		size_t GetScore() const override { return 20; }
		int GetColor() const override { return Engine::Terminal::CYAN; }

	protected:
		void InitModel() override
		{
			animationModel1 = &MODEL_1;
			animationModel2 = &MODEL_2;
			SetModel(MODEL_1);
		}
	};

	const Engine::Model AlienMidScore::MODEL_1
	(
		4,
		{
			'(', 'o', 'O', ')',
			'V', '~', '~', 'v'
		}
	);

	const Engine::Model AlienMidScore::MODEL_2
	(
		4,
		{
			'(', 'O', 'o', ')',
			'v', '~', '~', 'V'
		}
	);
}