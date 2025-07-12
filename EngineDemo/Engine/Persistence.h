#pragma once
#include <string>
#include <fstream>

namespace Engine
{
	namespace Persistence
	{
		inline void SaveBestScore(const char* persistenceFile, int bestScore)
		{
			std::ofstream outStream(persistenceFile);
			assert(outStream);
			outStream << bestScore;
		}

		inline int LoadBestScore(const char* persistenceFile)
		{
			std::ifstream infile(persistenceFile);

			if (!infile)
			{
				SaveBestScore(persistenceFile, -1);
				return -1;
			}

			int bestScore;
			infile >> bestScore;
			return bestScore;
		}
	}
}