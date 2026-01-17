#pragma once
#include <terme/Config.h>

#if DEBUG_MODE

#include <nbase_kit/singleton.h>
#include <terme/Managers/DebugManager.h>
#include <terme/Printers/DebugPrinter.h>
#include <list>
#include <string>
#include <memory>

namespace Engine
{
	class DebugManager : public nbase_kit::Singleton<DebugManager>
	{
		friend class nbase_kit::Singleton<DebugManager>;
		//---------------------------------------------------------- Settings
	private:
		static constexpr double kRefreshFpsEverySeconds = 0.5;
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