#pragma once
#include <memory>
#include <terme/managers/debug_manager.h>
#include <string>

namespace terme
{
	class i_simulation_entity : public std::enable_shared_from_this<i_simulation_entity>
	{
		friend class Simulation;
		//---------------------------------------------------------- Methods
	protected:
		virtual void Update() = 0;
		virtual ~i_simulation_entity() = default;
	};
}