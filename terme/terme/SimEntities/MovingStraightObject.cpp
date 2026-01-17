#include <terme/SimEntities/MovingStraightObject.h>



namespace Engine
{
	MovingStraightObject::MovingStraightObject(int x_pos, int y_pos, Direction move_dir, double move_speed)
		:Collider(x_pos, y_pos), move_direction_(move_dir), move_speed_(move_speed){ }

	void MovingStraightObject::Update()
	{
		Collider::Update();

                if (can_move_)
			TryMove(move_direction_, move_speed_);
	}
}