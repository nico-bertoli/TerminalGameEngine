#pragma once
#include "ISimulationEntity.h"
#include <vector>

namespace Platformer
{
    class ObstaclesSpawner : public Engine::ISimulationEntity
    {
        //---------------------------------------------------------- Fields
    private:
        int xPos;
        std::vector<double> minSpawnDelays;
        std::vector<double> maxSpawnDelays;
        std::vector<double> speeds;
        std::vector<int> ySpawnPoints;
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
            const std::vector<double>& minSpawnDelays,
            const std::vector<double>& maxSpawnDelays,
            const std::vector<double>& speeds,
            const std::vector<int>& ySpawnPoints,
            double increaseIntensityEverySeconds = -1,
            double stopSpawningWhenPhaseChangesDuration = 0
        );

        ObstaclesSpawner
        (
            int xPos,
            double spawnDelay,
            double speed,
            const std::vector<int>& ySpawnPoints
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