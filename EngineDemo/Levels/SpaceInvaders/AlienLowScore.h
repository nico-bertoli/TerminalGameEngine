#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienLowScore : public Alien
	{
	private:
		static inline const Engine::Model kModel1 = Engine::Model
		(
			4,
			{
				'[', ':', ':', ']',
				'/', '"', '"', '\\'
			}
		);
		static inline const Engine::Model kModel2 = Engine::Model
		(
			4,
			{
				'[', '.', '.', ']',
				'\\', '"', '"', '/'
			}
		);
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
}