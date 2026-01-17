#pragma once
#include <string>
#include <algorithm>

namespace string_utils
{
	void RemoveInstancesOfChar(std::string& str, char charToRemove)
	{
		str.erase(std::remove(str.begin(), str.end(), charToRemove), str.end());
	}
}