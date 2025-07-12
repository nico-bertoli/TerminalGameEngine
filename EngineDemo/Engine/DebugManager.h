#pragma once
#include "Config.h"

#if DEBUG_MODE

#include "Singleton.h"
#include "DebugPrinter.h"
#include <list>
#include <string>
#include <memory>

namespace Engine
{
	class DebugManager : public Singleton<DebugManager>
	{
		friend class Singleton;
		//---------------------------------------------------------- Settings
	private:
		static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
		//---------------------------------------------------------- Fields
		std::unique_ptr<DebugPrinter> debugPrinter;

		//fps
		std::list<double> fpsRecord;
		double lastTimePrintedFps = 0;
		double averageFPS = 0;

		//cout calls
		int coutCallsCount = 0;
		//---------------------------------------------------------- Methods
	public:
		void Reset(size_t screenSizeX, size_t screenSizeY, size_t screenPadding);
		void ShowAverageFPS();
		void IncrementCoutCalls();
		void PrintGenericLog(const std::string& str, int lineIndex);

	private:
		size_t GetAverageFps();
	};
}
#endif