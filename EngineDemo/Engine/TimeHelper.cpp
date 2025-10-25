#include "TimeHelper.h"
#include "Simulation.h"

#include <chrono>
#include <cmath>

using std::chrono::steady_clock;
using std::chrono::time_point;

namespace Engine
{
    void TimeHelper::OnFrameGenerated()
    {
        double currentTime = GetTime();
        deltaTime = currentTime - lastTimeFrameGenerated;
        lastTimeFrameGenerated = currentTime;
    }

    bool TimeHelper::IsTimeForFirstOfTwoModels(double changeModelEverySeconds) const
    {
        double time = GetTime();

        if (time == 0)
            return false;

        return std::fmod(time, changeModelEverySeconds) < changeModelEverySeconds / 2;
    }

    double TimeHelper::GetTime() const
    {
        time_point now = steady_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;
        return elapsed.count();
    }

    TimeHelper::TimeHelper()
    {
        Simulation::Instance().OnFrameGenerated.Subscribe([this]() { OnFrameGenerated(); });
        startTime = steady_clock::now();
    }
}
