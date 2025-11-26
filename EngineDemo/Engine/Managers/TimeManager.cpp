#include "Managers/TimeManager.h"
#include "Core/Simulation.h"

#include <chrono>
#include <cmath>

using std::chrono::steady_clock;
using std::chrono::time_point;

namespace Engine
{
    void TimeManager::OnFrameGenerated()
    {
        double currentTime = GetTime();
        deltaTime = currentTime - lastTimeFrameGenerated;
        lastTimeFrameGenerated = currentTime;
    }

    void TimeManager::OnSimulationStepped()
    {
        double currentTime = GetTime();
        fixedDeltaTime = currentTime - lastTimeSimulationStepped;
        lastTimeSimulationStepped = currentTime;
    }

    bool TimeManager::IsTimeForFirstOfTwoModels(double changeModelEverySeconds) const
    {
        double time = GetTime();

        if (time == 0)
            return false;

        return std::fmod(time, changeModelEverySeconds) < changeModelEverySeconds / 2;
    }

    double TimeManager::GetTime() const
    {
        time_point now = steady_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;
        return elapsed.count();
    }

    TimeManager::TimeManager()
    {
        Simulation::Instance().OnFrameGenerated.Subscribe([this]() { OnFrameGenerated(); });
        Simulation::Instance().OnSimulationStepped.Subscribe([this]() { OnSimulationStepped(); });
        startTime = steady_clock::now();
    }
}
