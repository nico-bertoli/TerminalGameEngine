#pragma once
#include "GameObject.h"
#include <optional>

namespace Platformer
{
	class SortingLayerTestObject : public Engine::GameObject
	{
	private:
		size_t sizeX;
		size_t sizeY;
		char modelChar;
		int color;
		size_t sortingLayer;
		double moveSpeed;
		std::optional<Engine::Direction> mainDirection;
		Engine::Model model;

	public:
		SortingLayerTestObject
		(
			int xPos,
			int yPos,
			size_t sizeX,
			size_t sizeY,
			char modelChar,
			int color,
			size_t sortingLayer,
			double moveSpeed = 0,
			std::optional<Engine::Direction> mainDirection = std::nullopt
		);

		bool CanExitScreenSpace() const override { return true; }
		double GetGravityScale() const override { return 0; }
		int GetColor() const override { return color; }
		size_t GetSortingLayer() const override { return sortingLayer; }

	protected:
		void InitModel() override;
		void Update()override;
	};
}