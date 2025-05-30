#pragma once
#include "ISimulationEntity.h"
#include <vector>

using std::vector;

namespace Platformer
{
    class ObstaclesSpawner : public Engine::ISimulationEntity
    {
        //---------------------------------------------------------- Fields
    private:
        int xPos;
        vector<double> minSpawnDelays;
        vector<double> maxSpawnDelays;
        vector<double> speeds;
        vector<int> ySpawnPoints;
        size_t spawnIntensity = 0;
        double stopSpawningWhenPhaseChangesDuration;
        double increaseIntensityEverySeconds;
        double spawnNextProjectileTime;
        double lastTimeIncreasedIntensity = 0;

        //---------------------------------------------------------- Methods
    public:
        ObstaclesSpawner
        (
            int xPos,
            const vector<double>& minSpawnDelays,
            const vector<double>& maxSpawnDelays,
            const vector<double>& speeds,
            const vector<int>& ySpawnPoints,
            double increaseIntensityEverySeconds = -1,
            double stopSpawningWhenPhaseChangesDuration = 0
        );

        ObstaclesSpawner
        (
            int xPos,
            double spawnDelay,
            double speed,
            const vector<int>& ySpawnPoints
        );

    protected:
        void Update() override;

    private:
        double GetCurrentMinSpawnDelay() const { return minSpawnDelays[spawnIntensity]; }
        double GetCurrentMaxSpawnDelay() const { return maxSpawnDelays[spawnIntensity]; }
        double GetCurrentObstaclesSpeed() const { return speeds[spawnIntensity]; }
        double GetNextSpawnObstacleTime() const;
        void TryIncreaseIntensity(double time);
    };
}