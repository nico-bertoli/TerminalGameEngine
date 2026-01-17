#pragma once
#include <terme/sim_entities/i_simulation_entity.h>
#include <terme/utils/direction_utils.h>
#include <terme/sim_entities/game_object.h>
#include <array>
#include <optional>

namespace terme
{
	class Particle : public game_object
	{
	//----------------------------------------- Fields
	private:
		std::array<Direction, 2> move_directions_;
		std::array<double, 2> move_speeds_;

		char model_char_;
		size_t remaining_movements_before_destruction_;
		TerminalColor color_;
		Model model_;

	//----------------------------------------- Methods
	public:
		Particle
		(
			int x_pos,
			int y_pos,
			char model_char,
			TerminalColor color,
			double move_speed,
			size_t movement_life_time,
			std::optional<Direction> main_direction
		);

		bool CanExitScreenSpace() const override { return true; }
		double GetGravityScale() const override { return 0; }
		TerminalColor GetColor() const override { return color_; }
		size_t GetSortingLayer() const override { return 200; }

	protected:
		void InitModel()override;
		void Update()override;

	private:
		void OnMoveCallback();
	};
}