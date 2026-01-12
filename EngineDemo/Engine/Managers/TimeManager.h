#pragma once
#include <nbase_kit/singleton.h>

#include <chrono>
#include <math.h>

namespace Engine
{
    class TimeManager : public nbase_kit::Singleton<TimeManager>
    {
        friend class nbase_kit::Singleton<TimeManager>;

        //---------------------------------------------------------- Fields
    private:
        std::chrono::steady_clock::time_point startTime;

        double lastTimeSimulationStepped = 0;
        double fixedDeltaTime; //updated every time simulation steps

        double lastTimeFrameGenerated = 0;
        double deltaTime = 1;  //updated only when any part of terminal is reprinted

        //---------------------------------------------------------- Methods
    public:
        double GetDeltaTime() const { return deltaTime; }
        double GetFPS() const { return 1.0 / GetDeltaTime();}

        double GetFixedDeltaTime() const {return fixedDeltaTime;}

        void OnFrameGenerated();
        void OnSimulationStepped();
        
        bool IsTimeForFirstOfTwoModels(double changeModelEverySeconds) const;
        double GetTime() const;

    private:
        TimeManager();
    };
}