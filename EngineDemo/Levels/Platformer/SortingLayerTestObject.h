#pragma once
#include "SimEntities/GameObject.h"
#include <optional>

namespace Platformer
{
	class SortingLayerTestObject : public Engine::GameObject
	{
	private:
		size_t size_x_;
		size_t size_y_;
		char model_char_;
		Engine::TerminalColor color_;
		size_t sorting_layer_;
		double move_speed_;
		std::optional<Engine::Direction> main_direction_;
		Engine::Model model_;

	public:
		SortingLayerTestObject
		(
			int x_pos,
			int y_pos,
			size_t size_x,
			size_t size_y,
			char model_char,
			Engine::TerminalColor color,
			size_t sorting_layer,
			double move_speed = 0,
			std::optional<Engine::Direction> main_direction = std::nullopt
		);

		bool CanExitScreenSpace() const override { return true; }
		double GetGravityScale() const override { return 0; }
		Engine::TerminalColor GetColor() const override { return color_; }
		size_t GetSortingLayer() const override { return sorting_layer_; }

	protected:
		void InitModel() override;
		void Update()override;
	};
}