#include "Particle.h"
#include "RandomUtils.h"
#include "DirectionUtils.h"
#include "Simulation.h"

using std::weak_ptr;

namespace Engine
{
	Particle::Particle
	(
		int xPos,
		int yPos,
		char modelChar,
		int color,
		double moveSpeed,
		size_t movesBeforeDestruction,
		std::optional<Direction> mainDirection
	)
		:
		GameObject(xPos, yPos),
		modelChar(modelChar),
		color(color),
		remainingMovementsBeforeDestruction(movesBeforeDestruction)
	{
		//--------- evaluate main direction

		if (!mainDirection.has_value()) //main direction = random value
		{
			moveDirections[0] = static_cast<Direction>(RandomUtils::GetRandomInt(0, Direction::COUNT - 1));
		}
		else //main direction is chosen randomly between given direction and orthogonal ones
		{
			moveDirections[0] = mainDirection.value();
		}

		//--------- evaluate orthogonal direction

		Direction orthogonalDirection = DirectionUtils::GetClockwiseDirection(moveDirections[0]);
		if (RandomUtils::GetRandomBool())
			orthogonalDirection = DirectionUtils::GetInverseDirection(orthogonalDirection);
		moveDirections[1] = orthogonalDirection;

		//--------- evaluate directions speeds

		double orthogonalSpeed = RandomUtils::GetRandomDouble(0, moveSpeed);
		moveSpeed -= orthogonalSpeed;

		moveSpeeds[0] = moveSpeed;
		moveSpeeds[1] = orthogonalSpeed;

		//--------- boost horizzontal speed (cause cells are smaller on x side)
		for (int i = 0; i < moveDirections.size(); ++i)
			if (DirectionUtils::IsDirectionHorizontal(moveDirections[i]))
				moveSpeeds[i] *= 2;

		OnMove.Subscribe([this](weak_ptr<GameObject> _, Direction __) { OnMoveCallback(); });
	}

	void Particle::InitModel()
	{
		model = CreteModelUsingChar(modelChar, 1, 1);
		SetModel(model);
	}

	void Particle::Update()
	{
		for (int i = 0; i < moveDirections.size(); ++i)
			TryMove(moveDirections[i], moveSpeeds[i]);
	}

	void Particle::OnMoveCallback()
	{
		if (--remainingMovementsBeforeDestruction == 0)
			Simulation::Instance().RemoveEntity(shared_from_this());
	}
}