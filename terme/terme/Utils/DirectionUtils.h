#pragma once
#include <stdexcept>
#include <cassert>

namespace Engine
{
	enum Direction { kUp, kDown, kLeft, kRight, kCount };
}

namespace DirectionUtils
{
	inline Engine::Direction GetInverseDirection(Engine::Direction direction)
	{
		switch (direction)
		{
		case Engine::Direction::kUp:
			return Engine::Direction::kDown;
		case Engine::Direction::kDown:
			return Engine::Direction::kUp;
		case Engine::Direction::kLeft:
			return Engine::Direction::kRight;
		case Engine::Direction::kRight:
			return Engine::Direction::kLeft;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	inline Engine::Direction GetClockwiseDirection(Engine::Direction direction)
	{
		switch (direction)
		{
		case Engine::Direction::kUp:
			return Engine::Direction::kRight;
		case Engine::Direction::kDown:
			return Engine::Direction::kLeft;
		case Engine::Direction::kLeft:
			return Engine::Direction::kUp;
		case Engine::Direction::kRight:
			return Engine::Direction::kDown;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	inline bool IsDirectionHorizontal(Engine::Direction dir)
	{
		assert(dir != Engine::Direction::kCount);
		return dir == Engine::Direction::kLeft || dir == Engine::Direction::kRight;
	}
}