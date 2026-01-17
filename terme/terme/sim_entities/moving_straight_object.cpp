#include <terme/sim_entities/moving_straight_object.h>



namespace terme
{
	moving_straight_object::moving_straight_object(int x_pos, int y_pos, Direction move_dir, double move_speed)
		:Collider(x_pos, y_pos), move_direction_(move_dir), move_speed_(move_speed){ }

	void moving_straight_object::Update()
	{
		Collider::Update();

                if (can_move_)
			TryMove(move_direction_, move_speed_);
	}
}