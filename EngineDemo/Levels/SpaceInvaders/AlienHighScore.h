#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienHighScore : public Alien
	{
	private:
		static const Engine::Model kModel1;
		static const Engine::Model kModel2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		size_t GetScore() const override { return 30; }
		Engine::TerminalColor GetColor() const override { return Engine::color::kMagenta; }

	protected:
		void InitModel() override
		{
			animation_model_1_ = &kModel1;
			animation_model_2_ = &kModel2;
			SetModel(kModel1);
		}
	};

	const Engine::Model AlienHighScore::kModel1
	(
		4,
		{
			'/', 'O',  'o',  '\\',
			'/', '\'', '\'', '\\'
		}
	);

	const Engine::Model AlienHighScore::kModel2
	(
		4,
		{
			'/', 'o', 'O', '\\',
			'|', '\'', '\'', '|'
		}
	);
}