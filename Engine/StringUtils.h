#pragma once
#include <string>

namespace StringUtils
{
	void RemoveInstancesOfChar(std::string& str, char charToRemove)
	{
		str.erase(std::remove(str.begin(), str.end(), charToRemove), str.end());
	}
}