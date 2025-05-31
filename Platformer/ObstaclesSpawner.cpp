#include "ObstaclesSpawner.h"
#include "Obstacle.h"
#include "Simulation.h"
#include "TimeHelper.h"
#include "RandomUtils.h"
#include "Collider.h"
#include <cstdlib>

using Engine::Collider;
using Engine::Direction;
using std::shared_ptr;

namespace Platformer
{
    ObstaclesSpawner::ObstaclesSpawner
    (
        int xPos,
        const std::vector<double>& minSpawnDelays,
        const std::vector<double>& maxSpawnDelays,
        const std::vector<double>& speeds,
        const std::vector<int>& ySpawnPoints,
        double increaseIntensityEverySeconds,
        double stopSpawningWhenPhaseChangesDuration
    ) :
        xPos(xPos),
        minSpawnDelays(minSpawnDelays),
        maxSpawnDelays(maxSpawnDelays),
        speeds(speeds),
        increaseIntensityEverySeconds(increaseIntensityEverySeconds),
        stopSpawningWhenPhaseChangesDuration(stopSpawningWhenPhaseChangesDuration),
        ySpawnPoints(ySpawnPoints)
    {
        assert(maxSpawnDelays.size() == speeds.size() && minSpawnDelays.size() == speeds.size());
        spawnNextProjectileTime = GetNextSpawnObstacleTime();
        lastTimeIncreasedIntensity = Engine::TimeHelper::Instance().GetTime();
    }

    ObstaclesSpawner::ObstaclesSpawner
    (
        int xPos,
        double spawnDelay,
        double speed,
        const std::vector<int>& ySpawnPoints
    ) :
        ObstaclesSpawner(
            xPos,
            std::vector<double>{spawnDelay},
            std::vector<double>{spawnDelay},
            std::vector<double>{speed},
            ySpawnPoints
        )
    {
    }

    void ObstaclesSpawner::Update()
    {
        double time = Engine::TimeHelper::Instance().GetTime();
        if (time >= spawnNextProjectileTime)
        {
            TryIncreaseIntensity(time);

            if (time - lastTimeIncreasedIntensity < stopSpawningWhenPhaseChangesDuration)
                return;

            spawnNextProjectileTime = GetNextSpawnObstacleTime();

            int randomIndex = RandomUtils::GetRandomInt(0, static_cast<int>(ySpawnPoints.size()) - 1);
            int randomPosY = ySpawnPoints[randomIndex];

            double obstacleSpeed = GetCurrentObstaclesSpeed();
            Direction direction = obstacleSpeed > 0 ? Direction::right : Direction::left;
            obstacleSpeed = abs(obstacleSpeed);
            shared_ptr<Obstacle> obstacle = std::make_shared<Obstacle>(xPos, randomPosY, direction, obstacleSpeed);
            Engine::Simulation::Instance().TryAddEntity(std::dynamic_pointer_cast<Collider>(obstacle));
        }
    }

    void ObstaclesSpawner::TryIncreaseIntensity(double time)
    {
        if (increaseIntensityEverySeconds == -1)
            return;

        if (spawnIntensity < speeds.size() - 1 && (time - lastTimeIncreasedIntensity) > increaseIntensityEverySeconds + stopSpawningWhenPhaseChangesDuration)
        {
            ++spawnIntensity;
            lastTimeIncreasedIntensity = time;
        }
    }

    double ObstaclesSpawner::GetNextSpawnObstacleTime() const
    {
        return Engine::TimeHelper::Instance().GetTime() + RandomUtils::GetRandomDouble(GetCurrentMinSpawnDelay(), GetCurrentMaxSpawnDelay());
    }
}