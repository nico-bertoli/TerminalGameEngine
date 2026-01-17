#pragma once
#include <terme/config.h>

#if DEBUG_MODE

#include <nbase_kit/singleton.h>
#include <terme/managers/debug_manager.h>
#include <terme/printers/debug_printer.h>
#include <list>
#include <string>
#include <memory>

namespace terme
{
	class debug_manager : public nbase_kit::Singleton<debug_manager>
	{
		friend class nbase_kit::Singleton<debug_manager>;
		//---------------------------------------------------------- Settings
	private:
		static constexpr double kRefreshFpsEverySeconds = 0.5;
		//---------------------------------------------------------- Fields
		std::unique_ptr<debug_printer> debugPrinter;

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