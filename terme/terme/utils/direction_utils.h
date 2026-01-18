#pragma once
#include <stdexcept>
#include <cassert>

namespace terme
{
	enum Direction { kUp, kDown, kLeft, kRight, kCount };
}

namespace DirectionUtils
{
	inline terme::Direction GetInverseDirection(terme::Direction direction)
	{
		switch (direction)
		{
		case terme::Direction::kUp:
			return terme::Direction::kDown;
		case terme::Direction::kDown:
			return terme::Direction::kUp;
		case terme::Direction::kLeft:
			return terme::Direction::kRight;
		case terme::Direction::kRight:
			return terme::Direction::kLeft;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	inline terme::Direction GetClockwiseDirection(terme::Direction direction)
	{
		switch (direction)
		{
		case terme::Direction::kUp:
			return terme::Direction::kRight;
		case terme::Direction::kDown:
			return terme::Direction::kLeft;
		case terme::Direction::kLeft:
			return terme::Direction::kUp;
		case terme::Direction::kRight:
			return terme::Direction::kDown;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	inline bool IsDirectionHorizontal(terme::Direction dir)
	{
		assert(dir != terme::Direction::kCount);
		return dir == terme::Direction::kLeft || dir == terme::Direction::kRight;
	}
}