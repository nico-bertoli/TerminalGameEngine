#include <terme/managers/time_manager.h>
#include <terme/core/simulation.h>

#include <chrono>
#include <cmath>

using std::chrono::steady_clock;
using std::chrono::time_point;

namespace terme
{
    void TimeManager::OnFrameGenerated()
    {
        double currentTime = GetTime();
        delta_time_ = currentTime - last_time_frame_generated_;
        last_time_frame_generated_ = currentTime;
    }

    void TimeManager::OnSimulationStepped()
    {
        double currentTime = GetTime();
        fixed_delta_time_ = currentTime - last_time_simulation_stepped_;
        last_time_simulation_stepped_ = currentTime;
    }

    bool TimeManager::IsTimeForFirstOfTwoModels(double change_model_every_seconds) const
    {
        double time = GetTime();

        if (time == 0)
            return false;

        return std::fmod(time, change_model_every_seconds) < change_model_every_seconds / 2;
    }

    double TimeManager::GetTime() const
    {
        time_point now = steady_clock::now();
        std::chrono::duration<double> elapsed = now - start_time_;
        return elapsed.count();
    }

    TimeManager::TimeManager()
    {
        Simulation::Instance().on_frame_generated.Subscribe([this]() { OnFrameGenerated(); });
        Simulation::Instance().on_simulation_stepped.Subscribe([this]() { OnSimulationStepped(); });
        start_time_ = steady_clock::now();
    }
}
