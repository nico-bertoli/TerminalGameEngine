#pragma once
#include <stdexcept>
#include <cassert>

namespace terme
{
	enum Direction { kUp, kDown, kLeft, kRight, kCount };

	namespace direction_utils
	{
		inline Direction GetInverseDirection(Direction direction)
		{
			switch (direction)
			{
			case Direction::kUp:
				return Direction::kDown;
			case Direction::kDown:
				return Direction::kUp;
			case Direction::kLeft:
				return Direction::kRight;
			case Direction::kRight:
				return Direction::kLeft;
			default:
				throw std::invalid_argument("Invalid direction");
			}
		}

		inline Direction GetClockwiseDirection(Direction direction)
		{
			switch (direction)
			{
			case Direction::kUp:
				return Direction::kRight;
			case Direction::kDown:
				return Direction::kLeft;
			case Direction::kLeft:
				return Direction::kUp;
			case Direction::kRight:
				return Direction::kDown;
			default:
				throw std::invalid_argument("Invalid direction");
			}
		}

		inline bool IsDirectionHorizontal(Direction dir)
		{
			assert(dir != Direction::kCount);
			return dir == Direction::kLeft || dir == Direction::kRight;
		}
	}
}