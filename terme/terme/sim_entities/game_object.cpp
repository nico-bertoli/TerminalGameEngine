#include <terme/sim_entities/game_object.h>
#include <terme/managers/time_manager.h>
#include <terme/core/simulation.h>

using std::shared_ptr;
using std::weak_ptr;

namespace terme
{
	game_object::game_object(int x_pos, int y_pos) :
		x_pos_(x_pos),
		y_pos_(y_pos),
		x_pos_continuous_(x_pos),
		y_pos_continuous_(y_pos)
	{
		ResetPartialMovement();
	}

	void game_object::Update()
	{
		ApplyGravity();
	}

	void game_object::ApplyGravity()
	{
		double gravity_scale = GetGravityScale();
		if (gravity_scale == 0)
			return;
		if (gravity_scale > 0)
			TryMove(Direction::kDown, gravity_scale);
		else
			TryMove(Direction::kUp, gravity_scale);
	}

	void game_object::TryMove(Direction direction, double move_speed)
	{
		if (can_move_ == false)
			return;

		move_speed = abs(move_speed);
		double delta_time = time_manager::Instance().GetFixedDeltaTime();

		switch (direction)
		{
		case Direction::kUp:
			y_pos_continuous_ += move_speed * delta_time;
			break;
		case Direction::kDown:
			y_pos_continuous_ -= move_speed * delta_time;
			break;
		case Direction::kRight:
			x_pos_continuous_ += move_speed * delta_time;
			break;
		case Direction::kLeft:
			x_pos_continuous_ -= move_speed * delta_time;
			break;
		}

		if (direction == Direction::kLeft || direction == Direction::kRight)
		{
			if (round(x_pos_continuous_) != x_pos_)
				Simulation::Instance().RequestMovement(std::dynamic_pointer_cast<game_object>(shared_from_this()), direction, move_speed);
		}
		else if (round(y_pos_continuous_) != y_pos_)
			Simulation::Instance().RequestMovement(std::dynamic_pointer_cast<game_object>(shared_from_this()), direction, move_speed);
	}

	Model game_object::CreteModelUsingChar(char model_char, size_t size_x, size_t size_y) const
	{
		Model result;
		result.Resize(size_x, size_y);

		for (auto& elem : result)
			elem = model_char;

		return result;
	}

	void game_object::SetModel(const Model& new_model)
	{
		if (model_ == &new_model)
			return;

		model_ = &new_model;

		Simulation::Instance().MarkAreaToReprint(std::dynamic_pointer_cast<game_object>(shared_from_this()));
	}

	void game_object::CALLED_BY_SIM_Move(Direction direction)
	{
		switch (direction)
		{
		case Direction::kUp:
			++y_pos_;
			y_pos_continuous_ = y_pos_;
			break;
		case Direction::kDown:
			--y_pos_;
			y_pos_continuous_ = y_pos_;
			break;
		case Direction::kRight:
			++x_pos_;
			x_pos_continuous_ = x_pos_;
			break;
		case Direction::kLeft:
			--x_pos_;
			x_pos_continuous_ = x_pos_;
			break;
		}
		on_move.Notify(std::dynamic_pointer_cast<game_object>(shared_from_this()), direction);
	}

	void game_object::InsertInListUsingRule(shared_ptr<game_object> obj, std::list<shared_ptr<game_object>>& list, bool(*insert_rule)(shared_ptr<game_object> new_item, std::shared_ptr<game_object> list_item))
	{
		auto it = list.begin();
		for (; it != list.end(); ++it)
			if(insert_rule(obj,*it))
				break;
		list.insert(it, obj);
	}

	void game_object::InsertInListUsingRule(shared_ptr<game_object> obj, std::list<weak_ptr<game_object>>& list, bool(*insert_rule)(shared_ptr<game_object> new_item, std::shared_ptr<game_object> list_item))
	{
		auto it = list.begin();
		for (; it != list.end(); ++it)
		{
			auto it_shared_ptr = it->lock();
			if (it_shared_ptr != nullptr && insert_rule(obj, it_shared_ptr))
				break;
		}
		list.insert(it, obj);
	}
}