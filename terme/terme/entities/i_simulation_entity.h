#pragma once
#include <memory>
#include <terme/managers/debug_manager.h>
#include <string>

namespace terme
{
	class ISimulationEntity : public std::enable_shared_from_this<ISimulationEntity>
	{
		friend class Simulation;
		//---------------------------------------------------------- Methods
	protected:
		virtual void Update() = 0;
		virtual ~ISimulationEntity() = default;
	};
}
