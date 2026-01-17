#include <terme/managers/debug_manager.h>

#if DEBUG_MODE

#include <terme/terminal/terminal.h>
#include <terme/managers/time_manager.h>

namespace terme
{
	void debug_manager::PrintGenericLog(const std::string& str, int lineIndex) { debugPrinter->PrintGenericLog(str, lineIndex); }

	void debug_manager::Reset
	(
		size_t screenSizeX,
		size_t screenSizeY,
		size_t screenPadding
	)
	{
		fpsRecord.clear();
		coutCallsCount = 0;

		debugPrinter = std::make_unique<debug_printer>(screenSizeX, screenSizeY, screenPadding);
	}

	void debug_manager::ShowAverageFPS()
	{
		if (debugPrinter != nullptr)
			debugPrinter->PrintFpsString(GetAverageFps());
	}

	size_t debug_manager::GetAverageFps()
	{
		double fps = time_manager::Instance().GetFPS();
		fpsRecord.push_back(fps);

		if (time_manager::Instance().GetTime() - lastTimePrintedFps > kRefreshFpsEverySeconds)
		{
			averageFPS = 0;

			for (double& fps : fpsRecord)
				averageFPS += fps;
			averageFPS /= fpsRecord.size();

			fpsRecord.clear();
			lastTimePrintedFps = time_manager::Instance().GetTime();
		}
		return static_cast<size_t>(averageFPS);
	}

	void debug_manager::IncrementCoutCalls()
	{
		if (debugPrinter == nullptr)
			return;

		if (++coutCallsCount == 1000)
			coutCallsCount = 0;
		debugPrinter->PrintCoutCallsCount(coutCallsCount);
	}

}
#endif