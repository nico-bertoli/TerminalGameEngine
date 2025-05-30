#pragma once
#include "Singleton.h"

#include <chrono>
#include <math.h>

namespace Engine
{
    class TimeHelper : public Singleton<TimeHelper>
    {
        friend class Singleton;

        //---------------------------------------------------------- Fields
    private:
        std::chrono::steady_clock::time_point startTime;
        double lastTimeFrameGenerated = 0;
        double deltaTime = 1;

        //---------------------------------------------------------- Methods
    public:
        double GetDeltaTime() const { return deltaTime; }
        double GetFPS() const { return 1.0 / GetDeltaTime(); }

        void OnFrameGenerated();
        bool IsTimeForFirstOfTwoModels(double changeModelEverySeconds) const;
        double GetTime() const;

    private:
        TimeHelper();
    };
}