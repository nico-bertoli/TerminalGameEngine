#pragma once
#include "ISimulationEntity.h"
#include "DirectionUtils.h"

namespace SpaceInvaders
{
	class UfoSpawner : public Engine::ISimulationEntity
	{
		//---------------------------------------------------------- Settings
	private:
		static const int MIN_SPAWN_DELAY = 15;
		static const int MAX_SPAWN_DELAY = 25;

		//---------------------------------------------------------- Fields
	private:
		int xSpawnPos;
		int ySpawnPos;
		Engine::Direction ufoMoveDirection;
		double lastTimeSpawned = -1;
		double nextSpawnTime = -1;

		//---------------------------------------------------------- Methods
	public:
		UfoSpawner(int xSpawnPos, int ySpawnPos, Engine::Direction ufoMoveDirection);
	protected:
		void Update()override;
	private:
		void SetNextSpawnDelay();
	};
}
