#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienLowScore : public Alien
	{
	private:
		static const Engine::Model MODEL_1;
		static const Engine::Model MODEL_2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		size_t GetScore() const override { return 10; }
		int GetColor() const override { return Engine::Terminal::YELLOW_DARK; }

	protected:
		void InitModel() override
		{
			animationModel1 = &MODEL_1;
			animationModel2 = &MODEL_2;
			SetModel(MODEL_1);
		}

	};

	const Engine::Model AlienLowScore::MODEL_1
	(
		4,
		{
			'[', ':', ':', ']',
			'/', '"', '"', '\\'
		}
	);

	const Engine::Model AlienLowScore::MODEL_2
	(
		4,
		{
			'[', '.', '.', ']',
			'\\', '"', '"', '/'
		}
	);
}