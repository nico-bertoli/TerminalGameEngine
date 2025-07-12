#pragma once
#include "Alien.h"

namespace SpaceInvaders
{
	class AlienHighScore : public Alien
	{
	private:
		static const Engine::Model MODEL_1;
		static const Engine::Model MODEL_2;
		//------------------------------------------------------ Methods
	public:
		using Alien::Alien;

		size_t GetScore() const override { return 30; }
		int GetColor() const override { return Engine::Terminal::MAGENTA; }

	protected:
		void InitModel() override
		{
			animationModel1 = &MODEL_1;
			animationModel2 = &MODEL_2;
			SetModel(MODEL_1);
		}
	};

	const Engine::Model AlienHighScore::MODEL_1
	(
		4,
		{
			'/', 'O',  'o',  '\\',
			'/', '\'', '\'', '\\'
		}
	);

	const Engine::Model AlienHighScore::MODEL_2
	(
		4,
		{
			'/', 'o', 'O', '\\',
			'|', '\'', '\'', '|'
		}
	);
}