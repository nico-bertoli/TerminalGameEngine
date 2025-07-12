#pragma once
#include <memory>
#include "DebugManager.h"
#include <string>

namespace Engine
{
	class ISimulationEntity : public std::enable_shared_from_this<ISimulationEntity>
	{
		friend class Simulation;
		//---------------------------------------------------------- Methods
	protected:
		virtual void Update() = 0;
		virtual ~ISimulationEntity() = default;

		/*virtual ~ISimulationEntity()
		{
			static int todoDeleteCounter = 0;
			Engine::DebugManager::Instance().PrintGenericLog(std::to_string(++todoDeleteCounter), 1);
		}*/
	};
}