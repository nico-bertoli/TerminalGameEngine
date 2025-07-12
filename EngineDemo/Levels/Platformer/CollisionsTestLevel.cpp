#include "CollisionsTestLevel.h"
#include "Config.h"
#include "Simulation.h"
#include "Obstacle.h"
#include "ObstaclesSpawner.h"

using std::shared_ptr;
using std::vector;

namespace Platformer
{
    void CollisionsTestLevel::LoadInSimulation()
    {
        Level::LoadInSimulation();
        Engine::Simulation& simulation = Engine::Simulation::Instance();

        //----------------------- spawners settings
        double spawnDelay = 0.15;
        double speed = 32;

        //----------------------- right spawner
        int xPosRight = 96;
        vector<int>ySpawnPoints = { 20,18,16,14 };
        shared_ptr<ObstaclesSpawner> spawnerRight = std::make_shared<ObstaclesSpawner>
        (
            xPosRight,
            spawnDelay,
            -speed,
            ySpawnPoints
        );
        simulation.TryAddEntity(spawnerRight);

        //----------------------- left spawner
        int xPosLeft = 2;
        vector<double>speeds2 = { 8, 1 };
        shared_ptr<ObstaclesSpawner> spawnerLeft = std::make_shared<ObstaclesSpawner>
        (
            xPosLeft,
            spawnDelay,
            speed,
            ySpawnPoints
        );
        simulation.TryAddEntity(spawnerLeft);
    }
}

