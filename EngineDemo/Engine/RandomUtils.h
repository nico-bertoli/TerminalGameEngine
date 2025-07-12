#pragma once
#include "TimeHelper.h"
#include <cmath>

namespace RandomUtils
{
	inline double GetRandomDouble(double min, double max)
	{
		double r = rand() / static_cast<double>(RAND_MAX);
		return ((max - min) * r + min);
	}

	inline int GetRandomInt(int minInclusive, int maxInclusive)
	{
		return minInclusive + std::rand() % (maxInclusive - minInclusive + 1);
	}

	inline bool GetRandomBool()
	{
		return GetRandomInt(0, 1) == 0;
	}
}