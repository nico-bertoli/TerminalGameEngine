#include "UfoSpawner.h"
#include "TimeHelper.h"
#include "Ufo.h"
#include "Simulation.h"
#include "RandomUtils.h"
#include "DebugManager.h"

using Engine::Direction;
using Engine::TimeHelper;
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
		if (TimeHelper::Instance().GetTime() > nextSpawnTime)
		{
			shared_ptr<Ufo> ufo = std::make_shared<Ufo>(xSpawnPos, ySpawnPos, ufoMoveDirection);
			Engine::Simulation::Instance().TryAddEntity(ufo);
			lastTimeSpawned = TimeHelper::Instance().GetTime();
			SetNextSpawnDelay();
		}
	}

	void UfoSpawner::SetNextSpawnDelay()
	{
		nextSpawnTime =
			TimeHelper::Instance().GetTime() +
			RandomUtils::GetRandomDouble(MIN_SPAWN_DELAY, MAX_SPAWN_DELAY);
	}
}