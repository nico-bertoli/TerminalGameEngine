#pragma once
#include "ISimulationEntity.h"
#include "DirectionUtils.h"
#include "GameObject.h"
#include <array>
#include <optional>

namespace Engine
{
	class Particle : public GameObject
	{
	private:
		std::array<Direction, 2> moveDirections;
		std::array<double, 2> moveSpeeds;

		char modelChar;
		size_t remainingMovementsBeforeDestruction;
		int color;
		Model model;

	public:
		Particle
		(
			int xPos,
			int yPos,
			char modelChar,
			int color,
			double moveSpeed,
			size_t movementLifeTime,
			std::optional<Direction> mainDirection
		);

		bool CanExitScreenSpace() const override { return true; }
		double GetGravityScale() const override { return 0; }
		int GetColor() const override { return color; }
		size_t GetSortingLayer() const override { return 200; }

	protected:
		void InitModel()override;
		void Update()override;

	private:
		void OnMoveCallback();
	};
}