#pragma once
#include <stdexcept>
#include <cassert>

namespace Engine
{
	enum Direction { up, down, left, right, COUNT };
}

namespace DirectionUtils
{
	inline Engine::Direction GetInverseDirection(Engine::Direction direction)
	{
		switch (direction)
		{
		case Engine::Direction::up:
			return Engine::Direction::down;
		case Engine::Direction::down:
			return Engine::Direction::up;
		case Engine::Direction::left:
			return Engine::Direction::right;
		case Engine::Direction::right:
			return Engine::Direction::left;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	inline Engine::Direction GetClockwiseDirection(Engine::Direction direction)
	{
		switch (direction)
		{
		case Engine::Direction::up:
			return Engine::Direction::right;
		case Engine::Direction::down:
			return Engine::Direction::left;
		case Engine::Direction::left:
			return Engine::Direction::up;
		case Engine::Direction::right:
			return Engine::Direction::down;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	inline bool IsDirectionHorizontal(Engine::Direction dir)
	{
		assert(dir != Engine::Direction::COUNT);
		return dir == Engine::Direction::left || dir == Engine::Direction::right;
	}
}