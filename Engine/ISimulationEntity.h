#pragma once
#include <memory>

namespace Engine
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