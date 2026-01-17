#include "UfoSpawner.h"
#include "Managers/TimeManager.h"
#include "Ufo.h"
#include "Core/Simulation.h"
#include "Utils/RandomUtils.h"
#include "Managers/DebugManager.h"

using Engine::Direction;
using Engine::TimeManager;
using std::shared_ptr;

namespace SpaceInvaders
{
	UfoSpawner::UfoSpawner(int xSpawnPos, int ySpawnPos, Direction ufoMoveDirection)
		: xSpawnPos(xSpawnPos), ySpawnPos(ySpawnPos), ufoMoveDirection(ufoMoveDirection)
	{
		SetNextSpawnDelay();
	}

	void UfoSpawner::Update()
	{
		if (TimeManager::Instance().GetTime() > nextSpawnTime)
		{
			shared_ptr<Ufo> ufo = std::make_shared<Ufo>(xSpawnPos, ySpawnPos, ufoMoveDirection);
			Engine::Simulation::Instance().TryAddEntity(ufo);
			lastTimeSpawned = TimeManager::Instance().GetTime();
			SetNextSpawnDelay();
		}
	}

	void UfoSpawner::SetNextSpawnDelay()
	{
		nextSpawnTime =
			TimeManager::Instance().GetTime() +
			RandomUtils::GetRandomDouble(kMinSpawnDelay, kMaxSpawnDelay);
	}
}