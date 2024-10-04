#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"

using Direction = GridDirection::Direction;

class UfoSpawner : public ISimulationEntity
{
//---------------------------------------------------------- Settings
private:
	static const int MIN_SPAWN_DELAY = 15;
	static const int MAX_SPAWN_DELAY = 25;

//---------------------------------------------------------- Fields
private:
	int xSpawnPos;
	int ySpawnPos;
	Direction ufoMoveDirection;
	double lastTimeSpawned = -1;
	double nextSpawnTime = -1;

//---------------------------------------------------------- Methods
public:
	UfoSpawner(int xSpawnPos, int ySpawnPos, Direction ufoMoveDirection);
protected:
	virtual void Update();
private:
	void SetNextSpawnDelay();
};