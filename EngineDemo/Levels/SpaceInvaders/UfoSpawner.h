#pragma once
#include "SimEntities/ISimulationEntity.h"
#include "Utils/DirectionUtils.h"

namespace SpaceInvaders
{
	class UfoSpawner : public Engine::ISimulationEntity
	{
		//---------------------------------------------------------- Settings
	private:
		static constexpr int kMinSpawnDelay = 15;
		static constexpr int kMaxSpawnDelay = 25;

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
