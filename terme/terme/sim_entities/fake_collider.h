#pragma once

#include <terme/sim_entities/collider.h>
#include <cassert>

namespace terme
{
	class fake_collider : public terme::Collider
	{
	public:
		fake_collider() : terme::Collider(0, 0) {}
	private:
		bool CanExitScreenSpace() const override { assert(false); return true; }
		double GetGravityScale() const override { assert(false); return 0; }
		void InitModel() override {}
	};
}