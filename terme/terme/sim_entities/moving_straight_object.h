#pragma once
#include <terme/sim_entities/collider.h>
#include <iostream>
#include <stdlib.h>
#include <cassert>

namespace terme
{
	class moving_straight_object : public Collider
	{
		//---------------------------------------------------------- Fields
	private:
		Direction move_direction_;
		const double move_speed_;

		//---------------------------------------------------------- Methods
	public:
		moving_straight_object(int x_pos, int y_pos, Direction move_dir, double move_speed);

	protected:
		void Update() override;
	};
}